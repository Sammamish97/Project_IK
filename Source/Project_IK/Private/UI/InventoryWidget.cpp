/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventoryWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UI/EquipBoardWidget.h"
#include "UI/RuneBoardWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	cur_hero_idx_ = 0;
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToRightHero);
	board_switch_button_->OnClicked.AddDynamic(this, &UInventoryWidget::ToggleBoard);
	board_switcher_->SetActiveWidget(equip_board_);
	scroll_box_->AddChild(wrap_box_);
}

void UInventoryWidget::NativeDestruct()
{
	switch_hero_left_button_->OnClicked.RemoveAll(this);
	switch_hero_right_button_->OnClicked.RemoveAll(this);
	Super::NativeDestruct();
}

void UInventoryWidget::InitInventoryWidget(UInventoryManager* inventory_manager)
{
	inventory_manager_cache_ = inventory_manager;
	data_table_cache_ =  Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();
}

void UInventoryWidget::ToggleBoard()
{
	if (board_switcher_->GetActiveWidgetIndex() == 0)
	{
		board_switcher_->SetActiveWidget(rune_board_);
	}
	else
	{
		board_switcher_->SetActiveWidget(equip_board_);
	}
}

void UInventoryWidget::SwitchToLeftHero()
{
	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
}

void UInventoryWidget::SwitchToRightHero()
{
	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
}
