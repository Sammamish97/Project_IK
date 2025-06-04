/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Header file for GameState.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "IKGameState.generated.h"

UCLASS()
class PROJECT_IK_API AIKGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AIKGameState();
};
