/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/WeaponMechanics.h"
#include "AIController.h"
#include "AI/GunnerAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Weapons/Guns/Gun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"
uint32 UWeaponMechanics::next_request_id_ = 0;

// Sets default values for this component's properties
UWeaponMechanics::UWeaponMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	head_socket_name_ = TEXT("head_socket");
	gun_socket_name_ = TEXT("rifle_socket");
	owned_cover_key_name_ = TEXT("OwnedCover");
}

// Called when the game starts
void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	owner_ref_ = Cast<AUnit>(GetOwner());
	weapon_actor_ = GetWorld()->SpawnActor<AGun>(weapon_class_);
	weapon_actor_->AttachToComponent(owner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, gun_socket_name_);
	StoreReloadRequestID();
}

//TODO: 무기의 장착과 실제 장착 후 생성은 분리되어야 한다.
//TODO: 인벤토리 프리뷰가 3D일때 역시 생각해야 한다.
void UWeaponMechanics::EquipWeapon(EWeaponType type)
{
	weapon_actor_->SetWeaponData(Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager()->GetWeaponData(type));
	weapon_actor_->SetGunOwner(GetOwner());
}

void UWeaponMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(burst_timer_handle_);

	if (weapon_actor_)
	{
		weapon_actor_->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

FDamageData UWeaponMechanics::GetWeaponFireDamageData()
{
	auto char_data = owner_ref_->GetCharacterStat()->GetCharacterData();
	float total_atk_dmg = weapon_actor_->GetWeaponData().basic_dmg_ + owner_ref_->GetCharacterStat()->GetAttackPower() * weapon_actor_->GetWeaponData().attack_scale;
	FDamageData dmg_data;
	dmg_data.atk_base_dmg = total_atk_dmg;
	dmg_data.damage_type = EDamageType::Projectile;
	dmg_data.attacker = owner_ref_;
	return dmg_data;
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	if (stop_fire_ == false)
	{
		TWeakObjectPtr<AActor> target_wptr = target;
		if (AActor* target_ptr = target_wptr.Get())
		{
			float total_fire_per_sec =  weapon_actor_->GetWeaponData().fire_per_sec * (1 + owner_ref_->GetCharacterStat()->GetAttackSpeed() / 100.f);
			float weapon_attack_speed = 1.f / total_fire_per_sec;
			if (on_burst_cool_down_ == false)
			{
				if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target_ptr)
				{
					FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UWeaponMechanics::OnFire, target_ptr, GetWeaponFireDamageData(), true, 0.f);
					GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, false, weapon_attack_speed); 
				}
			}
		}
	}
}

void UWeaponMechanics::OnFire(AActor* target, FDamageData dmg_data, bool is_controlled_fire, float offset)
{
	float total_crit_hit_rate = owner_ref_->GetCharacterStat()->GetCharacterData().critical_hit_rate_ + weapon_actor_->GetWeaponData().critical_hit_rate_;
	if (FMath::RandRange(0.f, 100.f) < total_crit_hit_rate)
	{
		dmg_data.atk_base_dmg *= 2;
		owner_ref_->DispatchUnitEvent(EUnitEvent::OnCriticalFire);
	}
	
	FireWeapon(target, dmg_data, is_controlled_fire, offset);
	owner_ref_->PlayAnimMontage(weapon_actor_->GetWeaponData().fire_montage_);
	burst_count_ += 1;
	if(IsMagazineEmpty())
	{
		FinishFire();
		return;
	}
	if (weapon_actor_->GetWeaponData().fire_type == EFireType::Burst && burst_count_ >= weapon_actor_->GetWeaponData().burst_amount)
	{
		on_burst_cool_down_ = true;
		FinishFire();
		FTimerDelegate burst_del = FTimerDelegate::CreateUObject(this, &UWeaponMechanics::FinishBurstCooldown);
		float burst_wait_time = weapon_actor_->GetWeaponData().wait_after_fire / (1 + owner_ref_->GetCharacterStat()->GetAttackSpeed() / 100.f);
		GetWorld()->GetTimerManager().SetTimer(burst_timer_handle_, burst_del, burst_wait_time, false); 
	}
}

void UWeaponMechanics::FireWeapon(AActor* target, FDamageData dmg_data, bool is_controlled_fire, float offset)
{
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		ACharacter* casted_character = Cast<ACharacter>(casted_target);
		if (is_controlled_fire)
		{
			if(UBlackboardComponent* blackboard = Cast<AAIController>(casted_character->GetController())->GetBlackboardComponent())
			{
				UObject* cover = blackboard->GetValueAsObject(owned_cover_key_name_);
				if(IsValid(cover))
				{
					if(FMath::RandRange(0, 100) > 50)
					{
						weapon_actor_->FireWeapon(casted_character->GetMesh()->GetSocketLocation(head_socket_name_), dmg_data);
					}
					else
					{
						weapon_actor_->FireWeapon(target->GetActorLocation() - FVector(0, 0, 50), dmg_data);
					}
				}
				else
				{
					weapon_actor_->FireWeapon(target->GetActorLocation(), dmg_data);
				}
			}
		}
		else
		{
			FVector rand_vec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, offset);
			weapon_actor_->FireWeapon(target->GetActorLocation() + rand_vec, dmg_data);
		}
	}
}

void UWeaponMechanics::FinishFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
}

void UWeaponMechanics::FinishBurstCooldown()
{
	GetWorld()->GetTimerManager().ClearTimer(burst_timer_handle_);
	burst_count_ = 0;
	on_burst_cool_down_ = false;
}

void UWeaponMechanics::Reload(float duration_multiplier)
{
	if(weapon_actor_)
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false)
		{
			on_reloading_ = true;
			owner_ref_->DispatchUnitEvent(EUnitEvent::OnReload);
			weapon_actor_->OnReloadStub();
			FWeaponData weapon_data = GetWeaponData();
			float reload_play_rate = weapon_data.reload_montage_->GetPlayLength() / weapon_data.reload_duration / duration_multiplier;
			owner_ref_->PlayAnimMontage(weapon_actor_->GetWeaponData().reload_montage_, reload_play_rate);
			GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &UWeaponMechanics::OnReload, weapon_data.reload_duration * duration_multiplier);
		}
	}
}



void UWeaponMechanics::StopFire()
{
	FinishFire();
	FinishBurstCooldown();
	stop_fire_ = true;
}

void UWeaponMechanics::ResumeFire()
{
	stop_fire_ = false;
}

void UWeaponMechanics::OnReload()
{
	if(weapon_actor_)weapon_actor_->Reload();
	on_reloading_ = false;
	burst_count_ = 0;
	FAIMessage Msg(TEXT("ReloadFinished"), this, reload_request_id_, FAIMessage::Success);
	FAIMessage::Send(owner_ref_, Msg);
	//IKTODO: 각 AIMessage를 사용할 때 마다 새로운 ID를 써야하는가? 더 많은 데이터가 필요하다.
	//reload_request_id_ = FAIRequestID::InvalidRequest;
}

void UWeaponMechanics::OnStunned()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
}

void UWeaponMechanics::OnDestroy()
{
	if(weapon_actor_) weapon_actor_->Destroy();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return weapon_actor_->IsMagazineEmpty();
}

FWeaponData UWeaponMechanics::GetWeaponData()
{
	if (weapon_actor_)
	{
		return weapon_actor_->GetWeaponData();
	}
	//TODO: 적절한 예외처리가 필요하다.
	return FWeaponData();
}

AGun* UWeaponMechanics::GetWeaponActor()
{
	return weapon_actor_;
}

bool UWeaponMechanics::IsOnReloading() const
{
	return on_reloading_;
}

FTimerHandle& UWeaponMechanics::RentFireTimerHandle()
{
	return fire_timer_handle_;
}
