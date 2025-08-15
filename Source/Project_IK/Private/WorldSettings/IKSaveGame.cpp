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

UIKSaveGame::UIKSaveGame()
{
	//DeleteSaveFiles();
}

void UIKSaveGame::SavePerkDetails(FName key, FPerkNodeDetail detail)
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save =  UGameplayStatics::LoadGameFromSlot("Perks", 0);
		perk_node_map_ = Cast<UIKSaveGame>(perk_save)->perk_node_map_;
		if (perk_node_map_.Contains(key))
		{
			perk_node_map_.Remove(key);
		}
		perk_node_map_.Add(key, detail);
	}
	UGameplayStatics::SaveGameToSlot(this, "Perks", 0);
}

TOptional<FPerkNodeDetail> UIKSaveGame::LoadPerkDetails(FName key)
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("Perks", 0);
		auto perk_data = Cast<UIKSaveGame>(perk_save)->perk_node_map_;
		if (perk_data.Contains(key))
		{
			return perk_data[key];
		}
	}
	return NullOpt;
}

TOptional<TMap<FName, FPerkNodeDetail>> UIKSaveGame::LoadAllPerkDetails()
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("Perks", 0);
		return Cast<UIKSaveGame>(perk_save)->perk_node_map_;
	}
	return NullOpt;
}

void UIKSaveGame::SavePerkPoint(int32 perk_point)
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		perk_points_ = perk_point;
	}
	UGameplayStatics::SaveGameToSlot(this, "Perks", 0);
}

TOptional<int32> UIKSaveGame::LoadPerkPoint()
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("Perks", 0);
		return Cast<UIKSaveGame>(perk_save)->perk_points_;
	}
	return NullOpt; 
}

void UIKSaveGame::DeleteSaveFiles()
{
	UGameplayStatics::DeleteGameInSlot("Perks", 0);
}
