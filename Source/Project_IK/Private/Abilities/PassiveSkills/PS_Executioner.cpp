/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Source file for the Executioner passive skill.
					It gives attack speed for a second & reduce skill cooldown by a second.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_Executioner.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Structs/BuffStatusData.h"
#include "Characters/HeroBase.h"

void UPS_Executioner::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::OnEliminate, this, &UPS_Executioner::ApplyExecutionerBuff);
}

void UPS_Executioner::ApplyExecutionerBuff()
{
	//FBuffStatusData attack_speed(TEXT("ExecutionerBuff"), ECharacterStatType::AttackSpeed, buff_amount_, is_buff_percentage_, buff_duration_);

	AActor* hero = hero_cache_.Get();
	if (hero)
	{
		//IKTODO: 테스트 이후 정상화 시켜야 함.
		// AHeroBase* unit = Cast<AHeroBase>(hero);
		// unit->ApplyBuff(attack_speed);
		//TODO: 이후 Reduce Cooltime 다시 구현해야 함.
		//unit->ReduceCooltime(reduce_cooltime_amount_);
	}

}
