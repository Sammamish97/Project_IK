/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for the Tempest Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SetBonuses/SetBonus_Tempest.h"

#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffStatusData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Weapons/Guns/GunBase.h"

//2세트: 스킬 쿨다운 20% 감소
void USetBonus_Tempest::ActivateEdgeBonus()
{
	Super::ActivateEdgeBonus();
	//IKTODO: 테스트 이후 정상화 시켜야 함.
	//hero_cache_->ApplyBuff(FBuffStatusData(TEXT("GreatBow_Edge"), ECharacterStatType::SkillCoolDown, 20.f, true, true));
}

//3세트: 액티브 스킬을 발동할 시, 자동 장전
void USetBonus_Tempest::ActivateTriangleBonus()
{
	Super::ActivateTriangleBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Tempest::TriangleAutoReload);
}

//6세트: 스킬을 사용할 때 마다 쿨 다운 보너스를 5씩 얻음. 최대 30을 얻을 수 있음.
void USetBonus_Tempest::ActivateHexagonBonus()
{
	Super::ActivateHexagonBonus();
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_cache_, EUnitEvent::OnActiveSkill, this, &USetBonus_Tempest::HexagonCoolDownBuff);
}

void USetBonus_Tempest::TriangleAutoReload()
{
	hero_cache_->GetWeaponMechanics()->GetWeaponActor()->Reload();
}

void USetBonus_Tempest::HexagonCoolDownBuff()
{
	if (cur_buff_stack < 6)
	{
		cur_buff_stack += 1;
		//IKTODO: 테스트 이후 정상화 시켜야 함.
		// hero_cache_->RemoveBuff(cool_down_buff_name);
		// hero_cache_->ApplyBuff(FBuffStatusData{cool_down_buff_name, ECharacterStatType::SkillCoolDown, cur_buff_stack * 5.f, true, true});
	}
}