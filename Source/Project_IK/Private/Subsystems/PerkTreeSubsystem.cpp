/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.3.2025
Summary : Source file for Perk trees.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/PerkTreeSubsystem.h"

#include "Structs/PerkNode.h"
#include "Managers/EnumCluster.h"

const TArray<FPerkNode>& UPerkTreeSubsystem::GetTree() const
{
	return perks_;
}

void UPerkTreeSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	
	// Rule: Index 0 must be root of a tree.

	// Initialize Tree in here.

	perks_.Add(FPerkNode(ECharacterStatType::AttackPower, 2.f, 1, { 1, 3 }));
	perks_.Add(FPerkNode(ECharacterStatType::AttackPower, 2.f, 1, { 2 }));
	perks_.Add(FPerkNode(ECharacterStatType::AttackPower, 2.f, 1));

	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1.f, 1, { 4 }));
	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1.f, 1, { 5, 6, 7 }));


	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1, 1.f));
	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1, 1.f));
	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1, 1.f));
}

void UPerkTreeSubsystem::Deinitialize()
{
	Super::Deinitialize();
}