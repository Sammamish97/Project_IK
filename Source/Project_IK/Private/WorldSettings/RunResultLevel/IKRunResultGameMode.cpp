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

#include "Subsystems/AudioManagerSubsystem.h"

void AIKRunResultGameMode::BeginPlay()
{
	Super::BeginPlay();

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::RunResultAmbient);
}

void AIKRunResultGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (instance)
	{
		instance->ClearRunData();
	}


	Super::EndPlay(EndPlayReason);
}
