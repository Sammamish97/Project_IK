/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.17.2024
Summary : Source file for a slot UserWidget for Store.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/StoreSlot.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "UI/CheckboxButtonWidget.h"
#include "Components/TextBlock.h"
#include "UI/StoreWidget.h"

#include "Subsystems/AudioManagerSubsystem.h"

void UStoreSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	switch (item_data_.gear_type_)
	{
	case EGearType::ActiveSkill:
		store_widget_cache_->CreateActiveSkillPopupWidget(item_data_.active_skill_data_.thumbnail_,
			text_manager_cache_->GetActiveSkillNameText(item_data_.active_skill_data_.type_),
			text_manager_cache_->GetActiveSkillDetailText(item_data_.active_skill_data_.type_),
			item_data_.active_skill_data_.cool_time_);
		break;

	case EGearType::PassiveSkill:
		store_widget_cache_->CreatePassiveSkillPopupWidget(item_data_.passive_skill_data_.thumbnail_,
			text_manager_cache_->GetPassiveSkillNameText(item_data_.passive_skill_data_.type_),
			text_manager_cache_->GetPassiveSkillDetailText(item_data_.passive_skill_data_.type_));
		break;

	case EGearType::Weapon:
		store_widget_cache_->CreateWeaponPopupWidget(item_data_.weapon_data_.thumbnail_,
			text_manager_cache_->GetWeaponNameText(item_data_.weapon_data_.type_),
			text_manager_cache_->GetWeaponDetailText(item_data_.weapon_data_.type_),
			item_data_.weapon_data_.status_data_);
		break;

	case EGearType::Rune:
		store_widget_cache_->CreateRunePopupWidget(item_data_.rune_data_.thumbnail_,
				text_manager_cache_->GetRuneNameText(item_data_.rune_data_.set_type),
				text_manager_cache_->GetRuneDetail(item_data_.rune_data_.set_type),
				item_data_.rune_data_.set_type);
		break;
	default:
		break;
	}
}

void UStoreSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	store_widget_cache_->RemovePopupWidget();
}

FReply UStoreSlot::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	float pos_x, pos_y;
	UWidgetLayoutLibrary::GetMousePositionScaledByDPI(store_widget_cache_->GetOwningPlayer(), pos_x, pos_y);
	store_widget_cache_->SetPopupWidgetPos({pos_x, pos_y});
	return FReply::Unhandled();
}

void UStoreSlot::SetStoreWidgetCache(UStoreWidget* store_widget)
{
	store_widget_cache_ = store_widget;
}

void UStoreSlot::SetItemData(const FRewardData& item_data)
{
	item_data_ = item_data;
	if (item_data_.gear_type_ == EGearType::Rune)
	{
		rune_idx_border_->SetVisibility(ESlateVisibility::HitTestInvisible);
		rune_idx_text_->SetVisibility(ESlateVisibility::HitTestInvisible);
		rune_idx_text_->SetText(FText::AsNumber(item_data_.rune_data_.slot_number));
	}
}

void UStoreSlot::SetTexture(UTexture2D* texture)
{
	checkbox_button_->SetButtonTexture(texture);
}

void UStoreSlot::SetPrice(int32 price)
{
	price_ = price;
	price_text_->SetText(FText::AsNumber(price));
}

int32 UStoreSlot::GetPrice() const
{
	return price_;
}

bool UStoreSlot::IsChecked() const
{
	return checkbox_button_->IsChecked();
}

void UStoreSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (checkbox_button_)
	{
		checkbox_button_->OnCheckboxButtonClickedDelegate.AddDynamic(this, &UStoreSlot::ForwardButtonClick);
	}
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	text_manager_cache_ = instance->GetTextManager();
}

void UStoreSlot::NativeDestruct()
{
	Super::NativeDestruct();

	OnStoreSlotClickedDelegate.Clear();
}

void UStoreSlot::ForwardButtonClick()
{
	if (OnStoreSlotClickedDelegate.IsBound())
	{
		if (checkbox_button_->IsChecked())
		{
			UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Confirm);
		}
		else
		{
			UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Deny);
		}

		OnStoreSlotClickedDelegate.Broadcast();
	}
}
