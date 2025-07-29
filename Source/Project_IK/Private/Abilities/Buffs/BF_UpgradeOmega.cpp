/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.28.2025
Summary : Source file for a buff that upgrades hero Omega.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BF_UpgradeOmega.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

void UBF_UpgradeOmega::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);

	float max_hp = target->GetCharacterStat()->GetMaxHitPoint();
	target->ApplyStatusBuff(EBuffType::Upgrade_Gamma, FBuffStatusData(ECharacterStatType::AttackPower, max_hp * attack_power_scaler_, false, true));
	target->ApplyStatusBuff(EBuffType::Upgrade_Gamma, FBuffStatusData(ECharacterStatType::SkillPower, max_hp * skill_power_scaler_, false, true));

	target->AddBuffUI(buff_type_, display_data_);
}
