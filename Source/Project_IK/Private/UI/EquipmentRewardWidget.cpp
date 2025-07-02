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
#include "WorldSettings/IKHUD.h"

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
	// @@ TODO: number of requested data count may differ by acts.
	CreateCheckboxButton(equipments_.active_skills_, row, column);
	CreateCheckboxButton(equipments_.passive_skills_, row, column);
	CreateCheckboxButton(equipments_.runes_, row, column);
	CreateCheckboxButton(equipments_.weapons_, row, column);
}

void UEquipmentRewardWidget::OnConfirmButtonClicked()
{
	//IKTODO: Confirm Button이 눌리면 인벤토리로 이동해 선택한 장비를 장착할 수 있게 해야 한다.
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	// Update HUD status
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		hud->SwitchUIByState(ECombatEndState::ShowingMapUI);
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
