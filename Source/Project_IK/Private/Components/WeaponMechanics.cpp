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
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

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
	gunner_ref_ = Cast<AUnit>(GetOwner());
	weapon_actor_ = GetWorld()->SpawnActor<AGun>(weapon_class_);
	weapon_actor_->AttachToComponent(gunner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, gun_socket_name_);
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
	if (weapon_actor_)
	{
		weapon_actor_->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

void UWeaponMechanics::SetDamageData(FCharacterData char_data, FDamageData dmg_data)
{
	//dmg_data에는 시전자가 들어있는것을 기대한다.
	//여기서 최종 데미지가 결정된다.
	float total_atk_dmg = weapon_actor_->GetWeaponData().basic_dmg_ + char_data.attack_power_ * weapon_actor_->GetWeaponData().attack_ratio;
	float total_crit_hit_rate = char_data.critical_hit_rate_ + weapon_actor_->GetWeaponData().critical_hit_rate_;
	if (FMath::RandRange(0.f, 100.f) < total_crit_hit_rate)
	{
		total_atk_dmg *= 2;
	}
	dmg_data.atk_base_dmg = total_atk_dmg;
	dmg_data.damage_type = EDamageType::Projectile;
	damage_data_ = dmg_data;
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	float gun_as = 1.f / weapon_actor_->GetWeaponData().fire_per_sec;
	float unit_as = gunner_ref_->GetCharacterStat()->GetAttackSpeed();
	float total_as = gun_as / unit_as;
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target)
	{
		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UWeaponMechanics::OnFire, target);
		GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, total_as, true, 0); 
	}
}

void UWeaponMechanics::OnFire(AActor* target)
{
	FireWeapon(target);
	gunner_ref_->PlayAnimMontage(weapon_actor_->GetWeaponData().fire_montage_);
	if(IsMagazineEmpty())
	{
		FinishFire();
	}
}

void UWeaponMechanics::FireWeapon(AActor* target)
{
	if(weapon_actor_ && IsValid(target))
	{
		ACharacter* casted_target = Cast<ACharacter>(target);
		if(UBlackboardComponent* blackboard = Cast<AAIController>(casted_target->GetController())->GetBlackboardComponent())
		{
			UObject* cover = blackboard->GetValueAsObject(owned_cover_key_name_);
			if(IsValid(cover))
			{
				if(FMath::RandRange(0, 100) > 50)
				{
					weapon_actor_->FireWeapon(casted_target->GetMesh()->GetSocketLocation(head_socket_name_), damage_data_);
				}
				else
				{
					weapon_actor_->FireWeapon(target->GetActorLocation() - FVector(0, 0, 50), damage_data_);
				}
			}
			else
			{
				weapon_actor_->FireWeapon(target->GetActorLocation(), damage_data_);
			}
		}
	}
}

void UWeaponMechanics::FinishFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
}

void UWeaponMechanics::Reload()
{
	if(weapon_actor_)
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false)
		{
			Cast<AMeleeAIController>(gunner_ref_->Controller)->SetUnitState(EUnitState::Reloading);
			gunner_ref_->PlayAnimMontage(weapon_actor_->GetWeaponData().reload_montage_);
			GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &UWeaponMechanics::OnReload, GetWeaponData().reload_duration);
		}
	}
}

void UWeaponMechanics::OnReload()
{
	if(weapon_actor_)weapon_actor_->Reload();
	Cast<AMeleeAIController>(gunner_ref_->Controller)->SetUnitState(EUnitState::Forwarding);
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
