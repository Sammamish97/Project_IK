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
#include "Weapons/Gun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EquipManager.h"
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
	equip_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetEquipManager();
}

//TODO: 무기의 장착과 실제 장착 후 생성은 분리되어야 한다.
//TODO: 인벤토리 프리뷰가 3D일때 역시 생각해야 한다.
void UWeaponMechanics::EquipWeapon(EWeaponType type)
{
	equipped_weapon_data_ = equip_manager_cache_->GetWeaponData(type);
	if (equipped_weapon_actor_)
	{
		equipped_weapon_actor_->Destroy();
	}
	equipped_weapon_actor_ = Cast<AGun>(GetWorld()->SpawnActor(equipped_weapon_data_.weapon_class));
	equipped_weapon_actor_->AttachToComponent(gunner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, gun_socket_name_);
	SetWeaponOwner(GetOwner());
}

void UWeaponMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
	if (equipped_weapon_actor_)
	{
		equipped_weapon_actor_->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	float gun_as = 1.f / equipped_weapon_actor_->GetFireInterval();
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
	gunner_ref_->PlayAnimMontage(equipped_weapon_data_.fire_montage_);
	if(IsMagazineEmpty())
	{
		FinishFire();
	}
}

void UWeaponMechanics::FireWeapon(AActor* target)
{
	if(equipped_weapon_actor_ && IsValid(target))
	{
		int damage = gunner_ref_->GetCharacterStat()->GetAttackPower();
		ACharacter* casted_target = Cast<ACharacter>(target);
		if(UBlackboardComponent* blackboard = Cast<AAIController>(casted_target->GetController())->GetBlackboardComponent())
		{
			UObject* cover = blackboard->GetValueAsObject(owned_cover_key_name_);
			if(IsValid(cover))
			{
				if(FMath::RandRange(0, 100) > 50)
				{
					equipped_weapon_actor_->FireWeapon(casted_target->GetMesh()->GetSocketLocation(head_socket_name_), damage);
				}
				else
				{
					equipped_weapon_actor_->FireWeapon(target->GetActorLocation() - FVector(0, 0, 50), damage);
				}
			}
			else
			{
				equipped_weapon_actor_->FireWeapon(target->GetActorLocation(), damage);
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
	if(equipped_weapon_actor_)
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false)
		{
			gunner_ref_->PlayAnimMontage(equipped_weapon_data_.reload_montage_);
			GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &UWeaponMechanics::OnReload, GetReloadDuration());
		}
	}
}

void UWeaponMechanics::OnReload()
{
	if(equipped_weapon_actor_)equipped_weapon_actor_->Reload();
	Cast<AMeleeAIController>(gunner_ref_->Controller)->SetUnitState(EUnitState::Forwarding);
}

void UWeaponMechanics::OnStunned()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
}

void UWeaponMechanics::OnDestroy()
{
	if(equipped_weapon_actor_) equipped_weapon_actor_->Destroy();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return equipped_weapon_actor_->IsMagazineEmpty();
}

float UWeaponMechanics::GetFireInterval() const
{
	return equipped_weapon_actor_->GetFireInterval();
}

float UWeaponMechanics::GetReloadDuration() const
{
	return equipped_weapon_actor_->GetReloadDuration();
}

void UWeaponMechanics::SetWeaponOwner(TWeakObjectPtr<AActor> gun_owner)
{
	equipped_weapon_actor_->SetGunOwner(gun_owner);
}