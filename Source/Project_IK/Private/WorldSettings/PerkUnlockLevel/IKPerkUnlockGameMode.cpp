/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for game mode using PerkUnlockLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/PerkUnlockLevel/IKPerkUnlockGameMode.h"

#include "Structs/PerkTree.h"

void AIKPerkUnlockGameMode::BeginPlay()
{
	Super::BeginPlay();

	UPerkTree::Get();
}

void AIKPerkUnlockGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UPerkTree::Get()->Destroy();
}
