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
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UI/EquipBoardWidget.h"
#include "UI/EquipStorageWidget.h"
#include "UI/RuneBoardWidget.h"
#include "UI/RuneStorageWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	cur_hero_idx_ = 0;
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToRightHero);
	board_switch_button_->OnClicked.AddDynamic(this, &UInventoryWidget::ToggleBoard);

	equip_board_->LoadEquipBoard();
	equip_storage_->LoadEquipStorage();

	board_switcher_->SetActiveWidget(equip_board_);
	storage_switcher_->SetActiveWidget(equip_storage_);

	rune_board_->InitBoardData(rune_storage_);
	rune_storage_->InitStorageData(rune_board_);
}

void UInventoryWidget::NativeDestruct()
{
	switch_hero_left_button_->OnClicked.RemoveAll(this);
	switch_hero_right_button_->OnClicked.RemoveAll(this);
	board_switch_button_->OnClicked.RemoveAll(this);

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
		rune_storage_->UpdateRuneStorage();
		rune_board_->UpdateRuneBoard();

		rune_storage_->LoadRuneStorage(0);
		rune_board_->LoadRuneBoardWidget();
		
		storage_switcher_->SetActiveWidget(rune_storage_);
		board_switcher_->SetActiveWidget(rune_board_);
	}
	else
	{
		equip_board_->UpdateEquipBoard();
		
		equip_storage_->LoadEquipStorage();
		equip_board_->LoadEquipBoard();
		
		board_switcher_->SetActiveWidget(equip_board_);
		storage_switcher_->SetActiveWidget(equip_storage_);
	}
}

void UInventoryWidget::SwitchToLeftHero()
{
	rune_board_->UpdateRuneBoard();
	equip_board_->UpdateEquipBoard();

	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
	
	rune_board_->SetCurHeroIdx(cur_hero_idx_);
	equip_board_->SetCurHeroIdx(cur_hero_idx_);
	
	rune_board_->LoadRuneBoardWidget();
	equip_board_->LoadEquipBoard();
}

void UInventoryWidget::SwitchToRightHero()
{
	rune_board_->UpdateRuneBoard();
	equip_board_->UpdateEquipBoard();

	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
	
	rune_board_->SetCurHeroIdx(cur_hero_idx_);
	equip_board_->SetCurHeroIdx(cur_hero_idx_);
	
	rune_board_->LoadRuneBoardWidget();
	equip_board_->LoadEquipBoard();
}
