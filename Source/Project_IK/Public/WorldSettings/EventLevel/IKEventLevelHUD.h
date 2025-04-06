/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Level HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKEventLevelHUD.generated.h"

UCLASS()
class PROJECT_IK_API AIKEventLevelHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void AfterPickOption();
private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UEventWidget> event_widget_class_ = nullptr;

	UPROPERTY()
	TObjectPtr<UEventWidget> event_widget_ = nullptr;
};
