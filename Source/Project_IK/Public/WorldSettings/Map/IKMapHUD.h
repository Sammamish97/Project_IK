/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map Level HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKMapHUD.generated.h"

class UGlobalBuffDisplayer;

UCLASS()
class PROJECT_IK_API AIKMapHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ToggleMap();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> map_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UGlobalBuffDisplayer> global_buff_displayer_class_;

	UPROPERTY()
	TObjectPtr<UUserWidget> map_widget_;

	UPROPERTY()
	TObjectPtr<UGlobalBuffDisplayer> global_buff_displayer_;
};
