/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Level Game Mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/EventLevel/IKEventGameMode.h"

#include "Subsystems/AudioManagerSubsystem.h"

void AIKEventGameMode::BeginPlay()
{
	Super::BeginPlay();

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::EventAmbient);
}

void AIKEventGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}
