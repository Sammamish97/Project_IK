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

//상시 공속 20%
void USetBonus_Chariot::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	//TODO: 상시 효과는 Buff보다는, status를 올리는것이 바람직하다. 이후 바꿔야 한다.
	hero_cache_->ApplyBuff(FBuffData(TEXT("Chariot_Edge"), ECharacterStatType::AttackSpeed, 20, false, 100.f));
}

//장전시 2초간 공속 50%
void USetBonus_Chariot::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Chariot::TriangleBonus);
}

//장전시 2초간 치명타 확률 50%
void USetBonus_Chariot::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_Chariot::HexagonBonus);
}

FDamageData USetBonus_Chariot::TriangleBonus(FDamageData dmg_data)
{
	hero_cache_->ApplyBuff(FBuffData(TEXT("Chariot_Triangle"), ECharacterStatType::AttackSpeed, 50, false, 2.f));
	return dmg_data;
}

FDamageData USetBonus_Chariot::HexagonBonus(FDamageData dmg_data)
{
	hero_cache_->ApplyBuff(FBuffData(TEXT("Chariot_Triangle"), ECharacterStatType::CriticalHitRate, 50, false, 2.f));
	return dmg_data;
}

