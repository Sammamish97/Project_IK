/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SupportSkills/SP_InstantRepair.h"

#include "Characters/Unit.h"

USP_InstantRepair::USP_InstantRepair()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);
	cool_time_ = 2.f;
	cost_ = 3.f;

	test_buff_data_.buff_type_ = EBuffType::InstantRepair;
	test_buff_data_.thumbnail = nullptr;
	test_buff_data_.duration_ = 5.f;
	test_buff_data_.buff_status_.Add({ECharacterStatType::AttackSpeed, 1.5f, true});

	test_buff_data_2 = test_buff_data_;
	test_buff_data_2.duration_ = 3.f;
	test_buff_data_2.buff_status_.Add({ECharacterStatType::AttackPower, 1.5f, true});


	test_buff_data_.buff_type_ = EBuffType::Agility;
	
	test_buff_data_3 = test_buff_data_2;
	test_buff_data_3.duration_ = 4.f;
	test_buff_data_3.buff_status_.Add({ECharacterStatType::SkillPower, 1.5f, true});


	test_buff_data_3.buff_type_ = EBuffType::Berserker;
}

TOptional<FTargetParameters> USP_InstantRepair::ActivateSkill(const FTargetResult& target_result)
{
	if(target_result.target_actors_[0])
	{
		if (AUnit* target_unit = Cast<AUnit>(target_result.target_actors_[0]))
		{
			target_unit->AcquireShield(300.f, 3.f);
			target_unit->ApplyBuff(test_buff_data_);
			target_unit->ApplyBuff(test_buff_data_2);
			target_unit->ApplyBuff(test_buff_data_3);

		}
	}
	return Super::ActivateSkill(target_result);
}
