/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.12.2025
Summary : Header file for HP UI Core widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPUICore.generated.h"

class UProgressBar;

UCLASS(Abstract, Blueprintable)
class PROJECT_IK_API UHPUICore : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void InitHPWidget(float max_hp, float cur_hp);

	UFUNCTION()
	virtual void UpdateWidget(float cur_hp, float cur_shield);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> hp_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> shield_bar_;
	
	UPROPERTY(Transient)
	float max_hp_ = 0;

	UPROPERTY(Transient)
	float cur_max_hp_ = 0;
};
