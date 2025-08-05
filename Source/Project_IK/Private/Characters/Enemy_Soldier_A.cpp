/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.29.2025
Summary : Source file for Enemy Soldier A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_Soldier_A.h"

#include "Abilities/Buffs/BuffHandler.h"

void AEnemy_Soldier_A::BeginPlay()
{
	Super::BeginPlay();
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
}

void AEnemy_Soldier_A::OnEnterBattleOnce()
{
	Super::OnEnterBattleOnce();
	FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &AEnemy_Soldier_A::GetBonusPower);
	GetWorld()->GetTimerManager().SetTimer(preheat_timer_, timer_delegate, preheat_duration_, false);
}

void AEnemy_Soldier_A::GetBonusPower()
{
	buff_->ApplyBuff(this);
}
