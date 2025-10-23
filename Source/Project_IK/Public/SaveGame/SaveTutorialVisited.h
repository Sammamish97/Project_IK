/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 10.22.2025
Summary : Header file for save tutorial visited save game.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BaseSaveGame.h"
#include "SaveTutorialVisited.generated.h"

UCLASS()
class PROJECT_IK_API USaveTutorialVisited : public UBaseSaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, SaveGame)
	bool is_first_battle_ = true;

	UPROPERTY(VisibleAnywhere, SaveGame)
	bool is_first_inventory_ = true;
};
