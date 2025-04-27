/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Chariot Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Chariot.h"

#include "Characters/HeroBase.h"
#include "Structs/BuffData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

//2세트: 공격력 10% + 체력 10%
void USetBonus_Chariot::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	hero_cache_->ApplyBuff(FBuffData(TEXT("Chariot_Edge"), ECharacterStatType::AttackPower, 10.f, true, true));
	hero_cache_->ApplyBuff(FBuffData(TEXT("Chariot_Edge"), ECharacterStatType::HitPoints, 10.f, true, true));
}

//3세트: 장전 시 최대 체력의 15%에 해당하는 실드 획득.
void USetBonus_Chariot::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Chariot::GetShield, FName(TEXT("USetBonus_Chariot::TriangleBonus")));
}

//6세트: 적 처치/이동/CC기에 걸렸을 때 최대 체력의 15%에 해당하는 실드 획득 + 해당 실드의 지속시간 동안 10%의 흡혈 획득.
void USetBonus_Chariot::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnStun, this, &USetBonus_Chariot::GetShieldAndLifeSteal, FName(TEXT("USetBonus_Chariot::HexagonBonus")));
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnMove, this, &USetBonus_Chariot::GetShieldAndLifeSteal, FName(TEXT("USetBonus_Chariot::HexagonBonus")));
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnEliminate, this, &USetBonus_Chariot::GetShieldAndLifeSteal, FName(TEXT("USetBonus_Chariot::HexagonBonus")));
}

FDamageData USetBonus_Chariot::GetShield(FDamageData dmg_data)
{
	hero_cache_->AcquireShield(hero_cache_->GetCharacterStat()->GetHitPoint() * 0.15f, shield_duration_);
	return dmg_data;
}

FDamageData USetBonus_Chariot::GetShieldAndLifeSteal(FDamageData dmg_data)
{
	hero_cache_->AcquireShield(hero_cache_->GetCharacterStat()->GetHitPoint() * 0.15f, shield_duration_);
	hero_cache_->ApplyBuff(FBuffData("Chariot_Hexagon", ECharacterStatType::LifeSteal, life_steal_percentage, true, shield_duration_));

	return dmg_data;
}