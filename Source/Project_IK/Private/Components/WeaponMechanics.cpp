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

void UWeaponMechanics::EquipWeapon()
{
	//Weapon class는 C++에서 생성&Load하지 않는다. Gun들의 BP를 각 Hero/Enemy의  WeaponMechanics BP에서 설정해 줘야 한다.
	weapon_ref_ = Cast<AGun>(GetWorld()->SpawnActor(weapon_class_));
	weapon_ref_->AttachToComponent(gunner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, gun_socket_name_);
}

// Called when the game starts
void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	gunner_ref_ = Cast<AUnit>(GetOwner());
	EquipWeapon();
}

void UWeaponMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
	Super::EndPlay(EndPlayReason);
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	float gun_as = 1.f / weapon_ref_->GetFireInterval();
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
	gunner_ref_->PlayAnimMontage(fire_montage_);
	if(IsMagazineEmpty())
	{
		FinishFire();
	}
}

void UWeaponMechanics::FireWeapon(AActor* target)
{
	if(weapon_ref_ && IsValid(target))
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
					weapon_ref_->FireWeapon(casted_target->GetMesh()->GetSocketLocation(head_socket_name_), damage);
				}
				else
				{
					weapon_ref_->FireWeapon(target->GetActorLocation() - FVector(0, 0, 50), damage);
				}
			}
			else
			{
				weapon_ref_->FireWeapon(target->GetActorLocation(), damage);
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
	if(weapon_ref_)
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(reload_timer_handle_) == false)
		{
			gunner_ref_->PlayAnimMontage(reload_montage_);
			GetWorld()->GetTimerManager().SetTimer(reload_timer_handle_, this, &UWeaponMechanics::OnReload, GetReloadDuration());
		}
	}
}

void UWeaponMechanics::OnReload()
{
	if(weapon_ref_)weapon_ref_->Reload();
	Cast<AMeleeAIController>(gunner_ref_->Controller)->SetUnitState(EUnitState::Forwarding);
}

void UWeaponMechanics::OnStunned()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
	GetWorld()->GetTimerManager().ClearTimer(reload_timer_handle_);
}

void UWeaponMechanics::OnDestroy()
{
	if(weapon_ref_) weapon_ref_->Destroy();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return weapon_ref_->IsMagazineEmpty();
}

float UWeaponMechanics::GetFireInterval() const
{
	return weapon_ref_->GetFireInterval();
}

float UWeaponMechanics::GetReloadDuration() const
{
	return weapon_ref_->GetReloadDuration();
}

void UWeaponMechanics::SetWeaponOwner(TWeakObjectPtr<AActor> gun_owner)
{
	weapon_ref_->SetGunOwner(gun_owner);
}
