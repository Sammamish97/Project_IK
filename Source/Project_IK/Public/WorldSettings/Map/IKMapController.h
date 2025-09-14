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

class UPauseManager;
class UInputAction;

UCLASS()
class PROJECT_IK_API AIKMapController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void TogglePause();
protected:


	UPROPERTY()
	TObjectPtr<UPauseManager> pause_manager_;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPauseManager> pause_manager_class_;

	bool on_pause_ = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> player_input_mapping_context;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> toggle_pause_action_;
};
