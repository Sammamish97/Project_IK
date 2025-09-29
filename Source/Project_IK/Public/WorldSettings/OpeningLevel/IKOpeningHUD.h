/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.29.2025
Summary : Header file for opening level HUD.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKOpeningHUD.generated.h"

class UWidgetAnimation;
class UOpeningWidget;

UCLASS()
class PROJECT_IK_API AIKOpeningHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOpeningWidget> opening_widget_class_;

	UPROPERTY(Transient)
	TObjectPtr<UOpeningWidget> opening_widget_;
};
