/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.23.2025
Summary : Header file for status widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EventManager.h"
#include "StatusWidget.generated.h"

class UTextManager;
class UTextBlock;

UCLASS()
class PROJECT_IK_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void LoadStatusData(EHeroType hero_type);
	
private:
//Defense
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> hp_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> hp_val_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> armor_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> armor_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> dodge_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> dodge_value_;

//Offense
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_power_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_power_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_speed_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_speed_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> crit_rate_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> crit_rate_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> vamp_rate_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> vamp_rate_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_power_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_power_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_cool_down_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_cool_down_value_;

private:
	TObjectPtr<UTextManager> text_manager_cache_;
};