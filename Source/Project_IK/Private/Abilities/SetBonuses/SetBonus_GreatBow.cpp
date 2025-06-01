/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.21.2025
Summary : Source file for the GreatBow Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_GreatBow.h"
#include "Characters/HeroBase.h"
#include "Components/BulletDeathBlowEffectComponent.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Weapons/Guns/GunBase.h"

//2세트: 공격력 20% 증가.
void USetBonus_GreatBow::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	hero_cache_->ApplyBuff(FBuffData(TEXT("GreatBow_Edge"), ECharacterStatType::AttackPower, 20.f, true, true));
}

//3세트: 장전 시 액티브 쿨타임 1초 감소.
void USetBonus_GreatBow::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnReload, this, &USetBonus_GreatBow::TriangleReloadCoolDownBonus);
}

//6세트: 공격받은 적의 체력이 20% 미만인 일반 적 처형.
void USetBonus_GreatBow::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	hero_cache_->GetWeaponMechanics()->GetWeaponActor()->AddOnHitComponent(UBulletDeathBlowEffectComponent::StaticClass());
}

void USetBonus_GreatBow::TriangleReloadCoolDownBonus()
{
	hero_cache_->ApplyBuff({"GreatBow_Cooldown", ECharacterStatType::SkillCoolDown, 20.f, false, 8.f});
}
