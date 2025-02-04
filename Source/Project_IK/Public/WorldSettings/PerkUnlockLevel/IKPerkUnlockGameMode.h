/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for game mode using PerkUnlockLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IKPerkUnlockGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPerkUnlockGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

protected:

	virtual void BeginPlay() override;
};
