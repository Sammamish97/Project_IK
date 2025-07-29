/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.29.2025
Summary : Source file for Enemy Knight A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_Knight_A.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Components/CharacterStatComponent.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

void AEnemy_Knight_A::BeginPlay()
{
	Super::BeginPlay();
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnHPChanged(GetCharacterStat(), this, &AEnemy_Knight_A::OnHPThreshold);
}

void AEnemy_Knight_A::OnHPThreshold(float ratio)
{
	if (on_buff_ == false)
	{
		buff_->ApplyBuff(this);
		on_buff_ = true;
	}
}
