/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.28.2024
Summary : Source file of game mode for Gotcha level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/GotchaWorld/IKGotchaGameMode.h"

#include "Subsystems/AudioManagerSubsystem.h"

void AIKGotchaGameMode::BeginPlay()
{
	Super::BeginPlay();

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::GotchaAmbient);
}
