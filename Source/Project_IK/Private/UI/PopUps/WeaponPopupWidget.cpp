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
	FFormatNamedArguments args;
	FText base;
	
	base = text_manager->GetPopUpText("BasicDmg");
	args.Add("BasicDmg", FText::AsNumber(data.basic_dmg_));
	basic_dmg_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("ATP");
	args.Add("ATP", FText::AsNumber(data.attack_scale));
	attack_power_ratio_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("SKP");
	args.Add("SKP", FText::AsNumber(data.extra_skill_power_));
	skill_power_ratio_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("ATS");
	args.Add("ATS", FText::AsNumber(data.fire_per_sec));
	attack_speed_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("RANGE");
	args.Add("RANGE", FText::AsNumber(data.fire_range));
	range_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("CRIT");
	args.Add("CRIT", FText::AsNumber(data.critical_hit_rate_));
	crit_rate_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("MAGAZINE");
	args.Add("MAGAZINE", FText::AsNumber(data.max_magazine));
	max_magazine_text_->SetText( FText::Format(base, args));
	args.Empty();

	base = text_manager->GetPopUpText("RELOADDURATION");
	args.Add("RELOADDURATION", FText::AsNumber(data.reload_duration));
	reload_duration_text_->SetText( FText::Format(base, args));
	args.Empty();
}
