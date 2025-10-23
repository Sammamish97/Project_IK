/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Source file for Weapon Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/WeaponPopupWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Managers/TextManager.h"
#include "Structs/WeaponStatusData.h"
#include "WorldSettings/IKGameInstance.h"

void UWeaponPopupWidget::UpdateWeaponData(const FWeaponStatusData& data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();

	attack_power_ratio_text_->SetText(text_manager->GetPopUpText("ATP"));
	attack_power_ratio_value_->SetText(FText::AsNumber(data.attack_scale));

	skill_power_ratio_text_->SetText(text_manager->GetPopUpText("ESK"));
	skill_power_ratio_value_->SetText(FText::AsNumber(data.extra_skill_power_));

	attack_speed_text_->SetText(text_manager->GetPopUpText("ATS"));
	attack_speed_value_->SetText(FText::AsNumber(data.fire_per_sec));

	range_text_->SetText(text_manager->GetPopUpText("RANGE"));
	range_value_->SetText(FText::AsNumber(data.fire_range));

	crit_rate_text_->SetText(text_manager->GetPopUpText("CRIT"));
	crit_rate_value_->SetText(FText::AsNumber(data.critical_hit_rate_));

	max_magazine_text_->SetText(text_manager->GetPopUpText("MAGAZINE"));
	max_magazine_value_->SetText(FText::AsNumber(data.max_magazine));

	reload_duration_text_->SetText(text_manager->GetPopUpText("RELOADDURATION"));
	reload_duration_value_->SetText(FText::AsNumber(data.reload_duration));
}
