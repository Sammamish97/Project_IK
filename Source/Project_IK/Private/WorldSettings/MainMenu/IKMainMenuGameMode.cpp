/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Source file for Game mode in MainMenu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/MainMenu/IKMainMenuGameMode.h"

#include "Subsystems/AudioManagerSubsystem.h"

void AIKMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::MainmenuAmbient);
}
