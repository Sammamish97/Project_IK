/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.8.2025
Summary : Source file for a subsystem that manages perk progresses.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/PerkProgressSubsystem.h"

#include "Managers/EnumCluster.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SavePerkProgress.h"

void UPerkProgressSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void UPerkProgressSubsystem::SavePerkDetails(EPerkNodeType type, FPerkNodeDetail detail)
{
	if (perk_node_map_.Contains(type))
	{
		perk_node_map_.Remove(type);
	}
	perk_node_map_.Add(type, detail);
}

FPerkNodeDetail UPerkProgressSubsystem::LoadPerkDetails(EPerkNodeType key)
{
	if (perk_node_map_.Contains(key))
	{
		return perk_node_map_[key];
	}
	return FPerkNodeDetail();
}

TMap<EPerkNodeType, FPerkNodeDetail> UPerkProgressSubsystem::LoadAllPerkDetails()
{
	return perk_node_map_;
}

void UPerkProgressSubsystem::SavePerkPoint(int32 perk_point)
{
	perk_points_ = perk_point;
}

int32 UPerkProgressSubsystem::LoadPerkPoint()
{
	return perk_points_;
}

void UPerkProgressSubsystem::SavePerkDataToDisk()
{
	USavePerkProgress* save_game_instance = Cast<USavePerkProgress>(UGameplayStatics::CreateSaveGameObject(USavePerkProgress::StaticClass()));

	UPerkProgressSubsystem* subsystem = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	if (save_game_instance && subsystem)
	{
		save_game_instance->perk_node_map_ = subsystem->LoadAllPerkDetails();

		save_game_instance->perk_points_ = subsystem->LoadPerkPoint();
	}

	UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
}
