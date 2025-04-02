/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Header file for Game mode in Boss level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/BossLevel/IKBossGameMode.h"

#include "Kismet/GameplayStatics.h"

void AIKBossGameMode::BeginPlay()
{
	// @@ TODO: Implement game logic of boss gamemode.

	// Since it has nothing, redirect to run result level.
	UGameplayStatics::OpenLevel(GetWorld(), FName("RunResultLevel"));
}
