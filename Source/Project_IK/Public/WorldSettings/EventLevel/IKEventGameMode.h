/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Level Game Mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IKEventGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKEventGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
