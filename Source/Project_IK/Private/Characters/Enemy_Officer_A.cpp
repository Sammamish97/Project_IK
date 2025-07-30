/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.30.2025
Summary : Source file for Enemy Officer A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Characters/Enemy_Officer_A.h"

#include "Abilities/EnemySkills/OfficerShield.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

// Called when the game starts or when spawned
void AEnemy_Officer_A::BeginPlay()
{
	Super::BeginPlay();
	auto delegate_bridge = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	delegate_bridge->BindOnHPChanged(GetCharacterStat(), this, &AEnemy_Officer_A::OnHPChanged);
}

void AEnemy_Officer_A::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	force_shield_ptr_->Destroy();
	Super::EndPlay(EndPlayReason);
}

void AEnemy_Officer_A::OnHPChanged(float ratio)
{
	if (shield_hp_threshold_ >= ratio)
	{
		if (use_force_shield_ == false)
		{
			use_force_shield_ = true;
			UseForceShield();
		}
	}
}

void AEnemy_Officer_A::UseForceShield()
{
	force_shield_ptr_ = GetWorld()->SpawnActor<AOfficerShield>(force_shield_class_, GetActorLocation(), GetActorRotation());
	force_shield_ptr_->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}