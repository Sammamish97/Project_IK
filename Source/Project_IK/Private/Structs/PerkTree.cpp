/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.3.2025
Summary : Source file for Perk trees.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Structs/PerkTree.h"

#include "Structs/PerkNode.h"
#include "Managers/EnumCluster.h"

static UPerkTree* instance = nullptr;

UPerkTree::UPerkTree()
	:Super::UObject()
{

}

UPerkTree* UPerkTree::Get()
{
	if (instance == nullptr)
	{
		instance = NewObject<UPerkTree>();
		instance->Initialize();
		instance->AddToRoot();
	}

	return instance;
}

void UPerkTree::Initialize()
{
	// Initialize Tree in here.
	perks_.Add(FPerkNode(ECharacterStatType::AttackPower, 1.f, {1}));
	perks_.Add(FPerkNode(ECharacterStatType::Armor, 1.f, { 2 }));
	perks_.Add(FPerkNode(ECharacterStatType::ActiveSkillPower, 1.f));
}

void UPerkTree::Destroy()
{
	if (instance)
	{
		instance->RemoveFromRoot();
		instance = nullptr;
	}
}
