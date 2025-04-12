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
	switch_hero_left_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToLeftHero);
	switch_hero_right_button_->OnClicked.AddDynamic(this, &UInventoryWidget::SwitchToRightHero);
	board_switch_button_->OnClicked.AddDynamic(this, &UInventoryWidget::ToggleBoard);

	cur_hero_idx_ = 0;
	hero_name_text_->SetText(FText::FromName(data_table_cache_->GetCharacterData(IntToHeroType(cur_hero_idx_))->character_name_));

	equip_board_->LoadEquipBoard();
	equip_storage_->LoadEquipStorage();

	board_switcher_->SetActiveWidget(equip_board_);
	storage_switcher_->SetActiveWidget(equip_storage_);

	rune_board_->InitBoardData(rune_storage_);
	rune_storage_->InitStorageData(rune_board_);
}

void UInventoryWidget::NativeDestruct()
{
	UpdateInventoryData();
	
	switch_hero_left_button_->OnClicked.RemoveAll(this);
	switch_hero_right_button_->OnClicked.RemoveAll(this);
	board_switch_button_->OnClicked.RemoveAll(this);

	Super::NativeDestruct();
}

void UInventoryWidget::InitInventoryWidget(UInventoryManager* inventory_manager)
{
	inventory_manager_cache_ = inventory_manager;
	data_table_cache_ = Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();
	LoadInventoryData();
}

void UInventoryWidget::ToggleBoard()
{
	if (board_switcher_->GetActiveWidgetIndex() == 0)
	{
		rune_storage_->UpdateRuneStorage();
		rune_board_->UpdateRuneBoard();

		rune_storage_->LoadRuneStorage(0);
		rune_board_->LoadRuneBoardWidget();
        rune_board_->TurnOnSetBonusEffect();
		
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

void UInventoryWidget::UpdateInventoryData()
{
	rune_board_->UpdateRuneBoard();
	rune_storage_->UpdateRuneStorage();
	
	equip_board_->UpdateEquipBoard();
	equip_storage_->UpdateEquipStorage();
}

void UInventoryWidget::LoadInventoryData()
{
	rune_board_->LoadRuneBoardWidget();
	rune_storage_->LoadRuneStorage(0);
	
	equip_storage_->LoadEquipStorage();
	equip_board_->LoadEquipBoard();
}

void UInventoryWidget::SwitchToLeftHero()
{
	UpdateInventoryData();
	
	cur_hero_idx_ = FMath::Max(0, cur_hero_idx_ - 1);
	hero_name_text_->SetText(FText::FromName(data_table_cache_->GetCharacterData(IntToHeroType(cur_hero_idx_))->character_name_));

	rune_board_->SetCurHeroIdx(cur_hero_idx_);
	equip_board_->SetCurHeroIdx(cur_hero_idx_);
	
	rune_board_->LoadRuneBoardWidget();
    rune_board_->TurnOnSetBonusEffect();
	equip_board_->LoadEquipBoard();
}

void UInventoryWidget::SwitchToRightHero()
{
	UpdateInventoryData();
	
	cur_hero_idx_ = FMath::Min(cur_hero_idx_ + 1, 3);
	hero_name_text_->SetText(FText::FromName(data_table_cache_->GetCharacterData(IntToHeroType(cur_hero_idx_))->character_name_));

	rune_board_->SetCurHeroIdx(cur_hero_idx_);
	equip_board_->SetCurHeroIdx(cur_hero_idx_);
	
	rune_board_->LoadRuneBoardWidget();
	rune_board_->TurnOnSetBonusEffect();
	equip_board_->LoadEquipBoard();
}
