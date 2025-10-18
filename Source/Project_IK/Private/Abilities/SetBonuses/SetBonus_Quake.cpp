/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Source file for Quake Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Quake.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/HeroBase.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

//2세트: 스킬 위력 + 20%
void USetBonus_Quake::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	edge_buff_ = NewObject<UBuffHandler>(this, edge_buff_class_);
	edge_buff_->ApplyBuff(hero_cache_);
}

//3세트: 액티브 스킬을 발동 시 공격속도 + 15%
void USetBonus_Quake::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	triangle_buff_ = NewObject<UBuffHandler>(this, triangle_buff_class_);
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Quake::TriangleAttackSpeedBuff);
}

//6세트: 15초에 한번 액티브 스킬의 쿨다운이 80% 감소.
void USetBonus_Quake::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Quake::HexagonSkillEcho);
}

void USetBonus_Quake::TriangleAttackSpeedBuff()
{
	triangle_buff_->ApplyBuff(hero_cache_);
}

void USetBonus_Quake::HexagonSkillEcho()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(skill_echo_timer_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(skill_echo_timer_handle_, hexagon_effect_cooldown, false);
		hero_cache_->ReduceActiveSkillCoolDownPercentage(0.8);
	}
}