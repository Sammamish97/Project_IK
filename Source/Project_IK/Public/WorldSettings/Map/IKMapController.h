/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map level player controller class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IKMapController.generated.h"
UCLASS()
class PROJECT_IK_API AIKMapController : public APlayerController
{
	GENERATED_BODY()
	virtual void SetupInputComponent() override;

	void ChangeLevel(FKey key);
};
