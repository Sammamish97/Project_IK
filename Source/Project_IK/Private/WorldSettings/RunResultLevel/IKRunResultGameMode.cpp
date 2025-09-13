/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.31.2025
Summary : Source file for GameMode class used in RunResultLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/RunResultLevel/IKRunResultGameMode.h"

#include "WorldSettings/IKGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "SaveGame/SaveRunProgress.h"

void AIKRunResultGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AIKRunResultGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (instance)
	{
		instance->ClearRunData();
	}

	ManageSaveFilesAfterRun();


	Super::EndPlay(EndPlayReason);
}

void AIKRunResultGameMode::ManageSaveFilesAfterRun()
{
	FString run_progress_slot_name = USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName();

	if (UGameplayStatics::DoesSaveGameExist(run_progress_slot_name, 0))
	{
		UGameplayStatics::DeleteGameInSlot(run_progress_slot_name, 0);
	}

	GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>()->SavePerkDataToDisk();
}
