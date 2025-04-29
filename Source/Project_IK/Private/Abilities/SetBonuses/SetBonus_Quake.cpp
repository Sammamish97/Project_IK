/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Source file for Quake Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Quake.h"

#include "Characters/HeroBase.h"
#include "Structs/BuffData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

//2세트: 스킬 위력 + 20%
void USetBonus_Quake::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	hero_cache_->ApplyBuff(FBuffData(TEXT("Quake_Edge"), ECharacterStatType::SkillPower, 20.f, true, true));
}

//3세트: 액티브 스킬을 발동 시 공격속도 + 15%
void USetBonus_Quake::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
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
	hero_cache_->ApplyBuff(FBuffData(TEXT("Quake_Triangle"), ECharacterStatType::AttackSpeed, 15.f, true, triangle_buff_duration_));
}

void USetBonus_Quake::HexagonSkillEcho()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(skill_echo_timer_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(skill_echo_timer_handle_, hexagon_effect_cooldown, false);
		hero_cache_->ApplyBuff({"Quake_Hexagon", ECharacterStatType::SkillCoolDown,80.f, false, 1.f});
	}
}