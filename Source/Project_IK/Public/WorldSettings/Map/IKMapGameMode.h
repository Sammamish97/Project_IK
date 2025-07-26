/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map level game mode class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IKMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


	void HealHeroesAfterCombat();
};
