/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for the Viper Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonus_Viper.h"

#include "Characters/HeroBase.h"
#include "Components/BulletDebuffEffectComponent.h"
#include "Components/BulletViperEffectComponent.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffData.h"
#include "Weapons/Guns/Gun.h"

//2세트: 공격 속도20%
void USetBonus_Viper::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	hero_cache_->ApplyBuff(FBuffData(TEXT("Viper_Edge"), ECharacterStatType::AttackSpeed, 20.f, true, true));
}

//3세트: 장전 후 초탄에 받는 피해 20%증가 디버프 추가.
void USetBonus_Viper::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	hero_cache_->GetWeaponMechanics()->GetWeaponActor()->AddAfterReloadOnHitComponent(UBulletDebuffEffectComponent::StaticClass());
}

//6세트: 총알에 독사 도트딜 추가.
void USetBonus_Viper::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	hero_cache_->GetWeaponMechanics()->GetWeaponActor()->AddOnHitComponent(UBulletViperEffectComponent::StaticClass());
}
