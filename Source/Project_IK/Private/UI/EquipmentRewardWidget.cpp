/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.08.2025
Summary : Header file for equipment reward widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/EquipmentRewardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"
#include "Components/Button.h"

void UEquipmentRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// @@ TODO: number of requested data count may differ by acts.
	equipments_ = game_instance->GetDataTableManager()->GetUniqueEquipmentDataRandomly(NUM_CANDIDATES);

	PopulateCheckboxButtons();

	confirm_button_->OnClicked.AddDynamic(this, &UEquipmentRewardWidget::OnConfirmButtonClicked);
	for (UCheckboxButtonWidget* widget : equipment_widgets_)
	{
		widget->OnCheckboxButtonClickedDelegate.AddDynamic(this, &UEquipmentRewardWidget::OnCheckboxButtonClicked);
	}

	checked_equipment_num_ = 0;
}

void UEquipmentRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	equipment_widgets_.Empty();
	confirm_button_->OnClicked.Clear();
}

void UEquipmentRewardWidget::PopulateCheckboxButtons()
{
	int32 row = 0, column = 0;

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// @@ TODO: number of requested data count may differ by acts.
	UDataTableManager* data_table_manager = game_instance->GetDataTableManager();
	CreateCheckboxButton(equipments_.active_skills_, row, column);
	CreateCheckboxButton(equipments_.ooparts_, row, column);
	CreateCheckboxButton(equipments_.passive_skills_, row, column);
	for (const FRuneData& data : equipments_.runes_)
	{
		UCheckboxButtonWidget* cb = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
		if (cb)
		{
			UGridSlot* slot = equipment_container_->AddChildToGrid(cb, row, column);
			if (slot)
			{
				slot->SetPadding(FMargin(64.f, 16.f));
			}

			cb->SetButtonTexture(data_table_manager->GetRuneSetThumbnail(data.set_type));

			equipment_widgets_.Add(cb);
		}
	}
	CreateCheckboxButton(equipments_.weapons_, row, column);
}

void UEquipmentRewardWidget::OnConfirmButtonClicked()
{
	int32 index = 0;

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	AddToInventory(equipments_.active_skills_, index, inventory_manager);
	AddToInventory(equipments_.ooparts_, index, inventory_manager);
	AddToInventory(equipments_.passive_skills_, index, inventory_manager);
	AddToInventory(equipments_.weapons_, index, inventory_manager);

	for (const auto& data : equipments_.runes_)
	{
		if (equipment_widgets_[index]->IsChecked())
		{
			// Add it to inventory
			inventory_manager->AddRune(data);
		}

		index += 1;
	}
}

void UEquipmentRewardWidget::OnCheckboxButtonClicked()
{
	for (UCheckboxButtonWidget* widget : equipment_widgets_)
	{
		// Finish callbackfunction if toggled.
		if (ToggleCheckboxButton(widget))
		{
			return;
		}
	}
}

bool UEquipmentRewardWidget::ToggleCheckboxButton(UCheckboxButtonWidget* widget)
{
	if (widget->IsHovered())
	{
		if (widget->IsChecked())
		{
			if (checked_equipment_num_ < MAX_CHOICE)
			{
				++checked_equipment_num_;
			}
			else
			{
				// When user tries selecting items more than inventory capacity,
				// Toggle again to make it not pressed. 
				widget->ToggleChecked();
			}
		}
		else
		{
			--checked_equipment_num_;
		}
		return true;
	}
	return false;
}
