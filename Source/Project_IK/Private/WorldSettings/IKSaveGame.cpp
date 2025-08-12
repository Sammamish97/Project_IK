/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.25.2025
Summary : Source file for SaveGame.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKSaveGame.h"

#include "Kismet/GameplayStatics.h"

void UIKSaveGame::SavePerkDetails()
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save =  UGameplayStatics::LoadGameFromSlot("Perks", 0);
		perk_node_map_ = Cast<UIKSaveGame>(perk_save)->perk_node_map_;
		
	}
}

void UIKSaveGame::LoadPerkDetails()
{
}

void UIKSaveGame::LoadAllPerkDetails()
{
}

void UIKSaveGame::DeleteSaveFiles()
{
}
