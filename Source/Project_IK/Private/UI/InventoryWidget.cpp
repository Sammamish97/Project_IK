/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "UI/HeroEquipBoardWidget.h"
#include "UI/RuneBoardWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UInventoryWidget::InitInventoryWidget(UInventoryManager* inventory_manager)
{
	inventory_manager_cache_ = inventory_manager;
	data_table_cache_ = Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();
	LoadInventoryData(0);
}

void UInventoryWidget::LoadInventoryData(int32 hero_idx)
{
	hero_idx_cache_ = hero_idx;
	TArray hero_boards = {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_};
	rune_board_->LoadRuneBoardWidget(hero_idx);
	for (int i = 0; i < hero_boards.Num(); i++)
	{
		hero_boards[i]->LoadHeroData(i);
	}
	//TArray support_skills = {support_skill_0_, support_skill_1_, support_skill_2_};
}

void UInventoryWidget::UpdateSetBonusEffect()
{
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::NativeDestruct()
{
	UpdateInventoryData(hero_idx_cache_);

	Super::NativeDestruct();
}


void UInventoryWidget::UpdateInventoryData(int32 hero_idx)
{
	rune_board_->UpdateRuneBoard(hero_idx);
	
}