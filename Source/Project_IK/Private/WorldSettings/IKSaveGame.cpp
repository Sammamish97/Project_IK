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

void UIKSaveGame::SavePerkDetails(FName key, FPerkNodeDetail detail)
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save =  UGameplayStatics::LoadGameFromSlot("Perks", 0);
		perk_node_map_ = Cast<UIKSaveGame>(perk_save)->perk_node_map_;
		// if (perk_node_map_.Contains(key))
		// {
		// 	perk_node_map_.Remove(key);
		// }
		//perk_node_map_.Add(key, detail);
		UGameplayStatics::SaveGameToSlot(this, "Perks", 0);
	}
}

FPerkNodeDetail UIKSaveGame::LoadPerkDetails(FName key)
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("Perks", 0);
		auto perk_data = Cast<UIKSaveGame>(perk_save)->perk_node_map_;
		// if (perk_data.Contains(key))
		// {
		// 	return perk_data[key];
		// }
	}
	return FPerkNodeDetail();
}

void UIKSaveGame::DeleteSaveFiles()
{
}
