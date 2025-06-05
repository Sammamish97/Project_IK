/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.05.2025
Summary : Header file for HP UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HP_UI_Widget.generated.h"

class UProgressBar;
UCLASS()
class PROJECT_IK_API UHP_UI_Widget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitHPWidget(float max_hp);

	UFUNCTION(BlueprintCallable)
	void OnHPChanged(float hp_ratio);

	UFUNCTION(BlueprintCallable)
	void OnShieldChanged(float shield_ratio);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> hp_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> shield_bar_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> separator_;

	UPROPERTY(Transient)
	float max_hp_ = 0;

	UPROPERTY(Transient)
	float temp_max_hp_ = 0;

	UPROPERTY(Transient)
	float cur_hp_ = 0;

	UPROPERTY(Transient)
	float single_segment_amount_ = 50.f; 
};
