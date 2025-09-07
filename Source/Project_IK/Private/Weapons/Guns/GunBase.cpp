/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/Guns/GunBase.h"

#include "AIController.h"
#include "Characters/Unit.h"
#include "Components/ObjectPoolComponent.h"
#include "Abilities/OnHitComponents/BulletOnHitEffectComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Structs/DamageData.h"
#include "Weapons/Guns/Bullet.h"
#include "BrainComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CharacterStatComponent.h"
#include "Components/SphereComponent.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Subsystems/AudioManagerSubsystem.h"

AGunBase::AGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weapon_skeletal_mesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	bullet_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
	root_sphere_mesh_ = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphere"));

	weapon_skeletal_mesh_->SetCollisionProfileName(TEXT("NoCollision"));
	root_sphere_mesh_->SetCollisionProfileName(TEXT("NoCollision"));

	muzzle_socket_name_ = TEXT("muzzle");
	head_socket_name_ = TEXT("head_socket");
	owned_cover_key_name_ = TEXT("OwnedCover");

	fire_particle_component_ = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Fire Particle"));
	fire_particle_component_->SetupAttachment(weapon_skeletal_mesh_, muzzle_socket_name_);
	fire_particle_component_->SetAutoActivate(false);

	ejection_particle_component_ = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Ejection Particle"));
	ejection_particle_component_->SetupAttachment(weapon_skeletal_mesh_, FName("Door"));
	ejection_particle_component_->SetAutoActivate(false);


	SetRootComponent(root_sphere_mesh_);

	weapon_skeletal_mesh_->AttachToComponent(root_sphere_mesh_, FAttachmentTransformRules::KeepRelativeTransform);
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	InstantReload();
}

void AGunBase::InstantReload()
{
	cur_magazine_ = weapon_data_cache_.status_data_.max_magazine;
}

void AGunBase::Reload()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false && hold_action_ == false)
	{
		if (AUnit* gun_owner = weak_gun_owner_.Get())
		{
			float reload_duration = weapon_data_cache_.status_data_.reload_duration * (1 - gun_owner->GetCharacterStat()->GetReloadSpeedBonus());
			gun_owner->DispatchUnitEvent(EUnitEvent::OnReload);
			float reload_play_rate = reload_montage_->GetPlayLength() / reload_duration;
			gun_owner->PlayAnimMontage(reload_montage_, reload_play_rate);
			GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &AGunBase::OnReload, reload_duration);
		}
	}
}

void AGunBase::StopReload()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_))
	{
		if (AUnit* gun_owner = weak_gun_owner_.Get())
		{
			gun_owner->StopAnimMontage();
			GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
			AAIController* controller = Cast<AAIController>(gun_owner->GetController());
			if (controller)
			{
				auto bt_component = Cast<UBehaviorTreeComponent>(controller->GetBrainComponent());
				OnFinishReload.Broadcast(bt_component, true);
			}
		}
	}
}

void AGunBase::OnReload()
{
	is_first_bullet_on_magazine_ = true;
	InstantReload();
	
	if (AUnit* gun_owner = weak_gun_owner_.Get())
	{
		gun_owner->ResetUnitState();
		AAIController* controller = Cast<AAIController>(gun_owner->GetController());
		if (controller)
		{
			auto bt_component = Cast<UBehaviorTreeComponent>(controller->GetBrainComponent());
			OnFinishReload.Broadcast(bt_component, true);
		}
	}
}

void AGunBase::SpawnBullet(const FRotator& rotation, const FVector& translation, const FDamageData& dmg_data)
{
	if (ABullet* bullet = Cast<ABullet>(bullet_pool_component_->SpawnFromPool(rotation, translation)))
	{
		if (is_first_bullet_on_magazine_)
		{
			is_first_bullet_on_magazine_ = false;
			for (auto& elem : on_hit_after_reload_)
			{
				bullet->AddOnHitComponent(elem);
			}
		}

		for (auto& elem : on_hit_effect_classes_)
		{
			bullet->AddOnHitComponent(elem);
		}

		bullet->SetShooter(weak_gun_owner_);
		bullet->SetDamageData(dmg_data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
	}
}

void AGunBase::PlayFireFXs() const
{
	if (fire_particle_component_)
	{
		fire_particle_component_->Activate(true);
	}
	if (ejection_particle_component_)
	{
		ejection_particle_component_->Activate(true);
	}

	PlayFireSound();
}

// This function has built upon a condition that gun shot change happened only on heroes.
// In a situation that enemy has speicial skills changing fire SFX, this function need to be changed.
// But no worries, it would be easy.
void AGunBase::PlayFireSound() const
{
	if (AUnit* owner = weak_gun_owner_.Get())
	{
		if (owner->IsA<AHeroBase>())
		{
			EAudioType fire_sound = (temporary_gunshot_audio_type_ == EAudioType::NONE) ? gunshot_audio_type_ : temporary_gunshot_audio_type_;

			UAudioManagerSubsystem::Get(this)->PlayAtLocation(fire_sound, GetActorLocation());
			return;
		}
	}

	// Reduce volume of enemy gunshots
	UAudioManagerSubsystem::Get(this)->PlayAtLocation(gunshot_audio_type_, GetActorLocation(), 0.5f);
}

void AGunBase::OnGunDied()
{
	if (death_fx_system_)
	{
		weapon_skeletal_mesh_->SetVisibility(false);
		UNiagaraComponent* fx = UNiagaraFunctionLibrary::SpawnSystemAttached(death_fx_system_, weapon_skeletal_mesh_, FName(""), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
		fx->SetColorParameter(FName("Color"), FLinearColor::White);
	}

	GetWorld()->GetTimerManager().SetTimer(die_timer_, this, &AGunBase::OnDieFinished, 1.f);
}

void AGunBase::OnDieFinished()
{
	Destroy();
}

void AGunBase::RecoverGunShotSound()
{
	temporary_gunshot_audio_type_ = EAudioType::NONE;
	GetWorld()->GetTimerManager().ClearTimer(temporary_gunshot_sound_timer_);
}

void AGunBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);

	ClearOnHitComponents();
	ClearAfterReloadOnHitComponents();

	Destroy();
}

void AGunBase::FireSingleBullet(FVector target_pos, const FDamageData& dmg_data)
{
	auto muzzle_location = weapon_skeletal_mesh_->GetSocketTransform(muzzle_socket_name_).GetLocation();
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_location, target_pos);
	SpawnBullet(rotation, muzzle_location, dmg_data);
	cur_magazine_ -= 1;

	PlayFireFXs();
}

void AGunBase::FireBuckShot(FVector target_pos, const FDamageData& dmg_data)
{
	float TEMP_DISTANCE_TO_SPHERE = 100;
	float TEMP_SPHERE_RADIUS = 10;

	auto muzzle_location = weapon_skeletal_mesh_->GetSocketTransform(muzzle_socket_name_).GetLocation();

	FVector to_target_normalized = (target_pos - muzzle_location).GetSafeNormal();
	FVector sphere_center = muzzle_location + to_target_normalized * TEMP_DISTANCE_TO_SPHERE;

	int32 TEMP_SHOTGUN_PALLET = 5;
	for (int32 i = 0; i < TEMP_SHOTGUN_PALLET; ++i)
	{
		FVector randVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, TEMP_SPHERE_RADIUS);
		FVector end_loc = sphere_center + randVec;

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_location, end_loc);
		SpawnBullet(rotation, muzzle_location, dmg_data);
	}
	cur_magazine_ -= 1;

	PlayFireFXs();
}

void AGunBase::BeginFire(AActor* target)
{
}

void AGunBase::FinishFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
}

void AGunBase::Die()
{
	root_sphere_mesh_->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	weapon_skeletal_mesh_->SetCollisionProfileName(TEXT("Ragdoll"));
	weapon_skeletal_mesh_->SetSimulatePhysics(true);

	GetWorld()->GetTimerManager().SetTimer(die_timer_, this, &AGunBase::OnGunDied, 3.f);
}

bool AGunBase::IsMagazineEmpty() const
{
	return cur_magazine_ <= 0;
}

FWeaponStatusData AGunBase::GetWeaponStatusData() const
{
	return weapon_data_cache_.status_data_;
}

TObjectPtr<USkeletalMeshComponent> AGunBase::GetWeaponSkeletalMesh() const
{
	return weapon_skeletal_mesh_;
}

FName AGunBase::GetGrabSocketName() const
{
	return grab_socket_name_;
}

FName AGunBase::GetMuzzleSocketName() const
{
	return muzzle_socket_name_;
}

//이 함수에서 치명타 확률 계산이 이루어지기에, 총알이 발사될 때 마다 이 함수가 호출되어야 한다.
FDamageData AGunBase::GetWeaponFireDamageData()
{
	if (AUnit* gun_owner = weak_gun_owner_.Get())
	{
		UCharacterStatComponent* stat_component = gun_owner->GetCharacterStat();
		float total_atk_dmg = weapon_data_cache_.status_data_.basic_dmg_ + stat_component->GetAttackPower() * weapon_data_cache_.status_data_.attack_scale;
		float total_skill_dmg = stat_component->GetSkillPower() * weapon_data_cache_.status_data_.skill_power_scale;
		FDamageData dmg_data;
		dmg_data.atk_base_dmg_ = total_atk_dmg;
		dmg_data.skill_power_base_dmg_ = total_skill_dmg;
		dmg_data.damage_type_ = EDamageType::Projectile;
		dmg_data.attacker_ = weak_gun_owner_;

		float total_crit_hit_rate = gun_owner->GetCharacterStat()->GetCriticalHitRate() + weapon_data_cache_.status_data_.critical_hit_rate_;
		OnCriticalRateCalculation.Broadcast(total_crit_hit_rate);
		if (FMath::RandRange(0.f, 100.f) < total_crit_hit_rate)
		{
			dmg_data.is_critical_shot_ = true;
			dmg_data.atk_base_dmg_ *= 2;
			gun_owner->DispatchUnitEvent(EUnitEvent::OnCriticalFire);
		}
		return dmg_data;
	}
	return FDamageData();
}

void AGunBase::SetHoldAction(bool hold_action)
{
	hold_action_ = hold_action;
}

void AGunBase::InitWeapon(const FWeaponData& data, TWeakObjectPtr<AUnit> gun_owner, bool is_hero)
{
	weapon_data_cache_ = data;
	weak_gun_owner_ = gun_owner;
	for (auto elem : bullet_pool_component_->GetObjectPool())
	{
		Cast<ABullet>(elem)->SetCollisionPreset(is_hero);
	}
	InstantReload();
}

void AGunBase::AddOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_component)
{
	on_hit_effect_classes_.Add(target_component);
}

void AGunBase::RemoveOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_component)
{
	on_hit_effect_classes_.Remove(target_component);
}

void AGunBase::ClearOnHitComponents()
{
	on_hit_effect_classes_.Empty();
}

void AGunBase::AddAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component)
{
	on_hit_after_reload_.Add(target_component);
}

void AGunBase::RemoveAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component)
{
	on_hit_after_reload_.Remove(target_component);
}

void AGunBase::ClearAfterReloadOnHitComponents()
{
	on_hit_after_reload_.Empty();
}

void AGunBase::ChangeGunShotSoundTemporariliy(EAudioType temporary_gunshot_audio, float duration)
{
	temporary_gunshot_audio_type_ = temporary_gunshot_audio;
	
	if (duration > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(temporary_gunshot_sound_timer_, this, &AGunBase::RecoverGunShotSound, duration);
	}
}
