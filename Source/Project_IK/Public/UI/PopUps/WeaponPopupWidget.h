/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Header file for Weapon Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BasicPopupWidget.h"
#include "WeaponPopupWidget.generated.h"

struct FWeaponStatusData;
class UTextBlock;
UCLASS()
class PROJECT_IK_API UWeaponPopupWidget : public UBasicPopupWidget
{
	GENERATED_BODY()
public:
	void UpdateWeaponData(const FWeaponStatusData& data);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> basic_dmg_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> basic_dmg_value_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_power_ratio_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_power_ratio_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_power_ratio_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_power_ratio_value_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_speed_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> attack_speed_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> range_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> range_value_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> crit_rate_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> crit_rate_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> max_magazine_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> max_magazine_value_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> reload_duration_text_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> reload_duration_value_;
};
