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
#include "BrainComponent.h"
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

// Sets default values for this component's properties
UWeaponMechanics::UWeaponMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	head_socket_name_ = TEXT("head_socket");
	owned_cover_key_name_ = TEXT("OwnedCover");
}

// Called when the game starts
void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	owner_ref_ = Cast<AUnit>(GetOwner());
}

//TODO: 무기의 장착과 실제 장착 후 생성은 분리되어야 한다.
//TODO: 인벤토리 프리뷰가 3D일때 역시 생각해야 한다.
void UWeaponMechanics::EquipWeapon(EWeaponType type)
{
	auto data_table_manager = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
	//IKTODO: weapon_class는 모든 WeaponMechanics를 사용하는 유닛 사이에 동일하다. 지금은 BP마다 Class를 꽃아주지만, 이후 바꿔야 한다.
	weapon_actor_ = GetWorld()->SpawnActor<AGun>(weapon_class_);
	weapon_actor_->SetWeaponData(data_table_manager->GetWeaponData(type));
	
	EWeaponAnimationType weapon_anim_type = GetWeaponData().anim_type;
	auto bone_type = owner_ref_->GetBoneType();
	
	TSoftObjectPtr<UAnimMontage> soft_fire_anim = data_table_manager->GetUnitWeaponAnimMontage(bone_type, weapon_anim_type, EWeaponAction::Fire);
	TSoftObjectPtr<UAnimMontage> soft_reload_anim = data_table_manager->GetUnitWeaponAnimMontage(bone_type, weapon_anim_type, EWeaponAction::Reload);
	
	fire_montage_ = soft_fire_anim.LoadSynchronous();
	reload_montage_ = soft_reload_anim.LoadSynchronous();
	if (GetWeaponData().fire_type == EFireType::PreHeating)
	{
		TSoftObjectPtr<UAnimMontage> soft_preheat_anim = data_table_manager->GetUnitWeaponAnimMontage(bone_type, weapon_anim_type, EWeaponAction::Preheat);
		preheat_montage_ = soft_preheat_anim.LoadSynchronous();
	}
	
	FName socket_name;
	switch (weapon_anim_type)
	{
	case EWeaponAnimationType::Pistol:
		socket_name = TEXT("pistol_socket");
		break;

	case EWeaponAnimationType::Rifle:
		socket_name = TEXT("rifle_socket");
		break;

	

	case EWeaponAnimationType::INVALID:
	default:
		break;
	}
	weapon_actor_->AttachToComponent(owner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, socket_name);
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
	UCharacterStatComponent* stat_component = owner_ref_->GetCharacterStat();
	float total_atk_dmg = weapon_actor_->GetWeaponData().basic_dmg_ + stat_component->GetAttackPower() * weapon_actor_->GetWeaponData().attack_scale;
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
					FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UWeaponMechanics::OnFire, target_ptr, GetWeaponFireDamageData(), weapon_attack_speed, true, 0.f);
					GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, true, FMath::Max(weapon_attack_speed, weapon_actor_->GetWeaponData().preheating_time));
					if (weapon_actor_->GetWeaponData().fire_type == EFireType::PreHeating)
					{
						//만약 총기를 예열해야 한다면, 예열 VFX(에너지 집중), 혹은 애니메이션(총열 회전)을 여기서 발동해야 함.
					}
				}
			}
		}
	}
}

void UWeaponMechanics::OnFire(AActor* target, FDamageData dmg_data, float attack_speed, bool is_controlled_fire, float offset)
{
	float total_crit_hit_rate = owner_ref_->GetCharacterStat()->GetCriticalHitRate() + weapon_actor_->GetWeaponData().critical_hit_rate_;
	OnCriticalRateCalculation.Broadcast(total_crit_hit_rate);
	if (FMath::RandRange(0.f, 100.f) < total_crit_hit_rate)
	{
		dmg_data.is_critical_shot_ = true;
		dmg_data.atk_base_dmg *= 2;
		owner_ref_->DispatchUnitEvent(EUnitEvent::OnCriticalFire);
	}
	
	FireWeapon(target, dmg_data, is_controlled_fire, offset);
	owner_ref_->PlayAnimMontage(fire_montage_, fire_montage_->GetPlayLength() / attack_speed);
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
	//IKTODO: 간헐적으로 target이 null이라 터짐.
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		ACharacter* casted_character = Cast<ACharacter>(casted_target);
		if (is_controlled_fire)
		{
			if(UBlackboardComponent* blackboard = Cast<AAIController>(casted_character->GetController())->GetBlackboardComponent())
			{
				UObject* cover = blackboard->GetValueAsObject(owned_cover_key_name_);
				//엄폐물이 있으면 확률에 따라 엄폐물에 사격.
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
				//엄폐물이 없다면 다이렉트하게 적에게 사격.
				else
				{
					weapon_actor_->FireWeapon(target->GetActorLocation(), dmg_data);
				}
			}
			//엄폐를 하지 않는 적(BB 없음)에게는 다이렉트하게 사격.
			else
			{
				weapon_actor_->FireWeapon(target->GetActorLocation(), dmg_data);
			}
		}
		//난사 중이면 랜덤 벡터를 더해서 사격.
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
			float reload_play_rate = reload_montage_->GetPlayLength() / weapon_data.reload_duration / duration_multiplier;
			owner_ref_->PlayAnimMontage(reload_montage_, reload_play_rate);
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
