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

void UIKSaveGame::CreateEmptySaveFile()
{
	perk_points_ = 0;
	perk_node_map_.Empty();
	UGameplayStatics::SaveGameToSlot(this, "Perks", 0);
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
	}
	perk_node_map_.Add(key, detail);
	UGameplayStatics::SaveGameToSlot(this, "Perks", 0);
}

FPerkNodeDetail UIKSaveGame::LoadPerkDetails(FName key)
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
	return FPerkNodeDetail();
}

TMap<FName, FPerkNodeDetail> UIKSaveGame::LoadAllPerkDetails()
{
	if (UGameplayStatics::DoesSaveGameExist("Perks", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("Perks", 0);
		return Cast<UIKSaveGame>(perk_save)->perk_node_map_;
	}
	return TMap<FName, FPerkNodeDetail>();
}

void UIKSaveGame::SavePerkPoint(int32 perk_point)
{
	if (UGameplayStatics::DoesSaveGameExist("PerkPoints", 0))
	{
		perk_points_ = perk_point;
	}
	UGameplayStatics::SaveGameToSlot(this, "PerkPoints", 0);
}

int32 UIKSaveGame::LoadPerkPoint()
{
	if (UGameplayStatics::DoesSaveGameExist("PerkPoints", 0))
	{
		auto perk_save = UGameplayStatics::LoadGameFromSlot("PerkPoints", 0);
		return Cast<UIKSaveGame>(perk_save)->perk_points_;
	}
	return -1; 
}

void UIKSaveGame::DeleteSaveFiles()
{
	UGameplayStatics::DeleteGameInSlot("Perks", 0);
	UGameplayStatics::DeleteGameInSlot("PerkPoints", 0);

}
