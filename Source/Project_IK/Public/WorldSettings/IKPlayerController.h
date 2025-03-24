/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Header file for Player Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IKPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AIKPlayerController();

	virtual void BeginPlay();
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();

	void UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	class UTargetingComponent* targeting_component_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> player_input_mapping_context;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> toggle_map_action;
};
