/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.28.2025
Summary : Source file for a buff that upgrades hero Beta.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BF_UpgradeBeta.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"


void UBF_UpgradeBeta::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);

	target->ApplyStatusBuff(EBuffType::Upgrade_Beta, FBuffStatusData(ECharacterStatType::MagazineBonus, target->GetCharacterStat()->GetAttackSpeed() * scaler_, false, true));

	target->AddBuffUI(buff_type_);
}
