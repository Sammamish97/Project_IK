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
#include "UI/HeroEquipBoardWidget.h"
#include "UI/RewardContainerWidget.h"
#include "UI/RuneBoardWidget.h"
#include "UI/InventorySlots/SupportSkillSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UInventoryWidget::InitInventoryWidget(UInventoryManager* inventory_manager)
{
	inventory_manager_cache_ = inventory_manager;
	
	//IKTODO: Data table이 필요없다면 삭제.
	data_table_cache_ = Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();

	reward_container_->SetInventoryWidgetCache(this);
	rune_board_->SetInventoryWidget(this);
	rune_board_->LoadRuneBoardWidget(0);
	
	TArray hero_boards = {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_};
	for (int32 i = 0; i < hero_boards.Num(); i++)
	{
		hero_boards[i]->LoadHeroData(i);
		hero_boards[i]->SetInventoryWidgetCache(this);
	}
	
	hero_board_0_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_0_Board_Clicked);
	hero_board_1_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_1_Board_Clicked);
	hero_board_2_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_2_Board_Clicked);
	hero_board_3_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_3_Board_Clicked);

	for (const auto& elem : {support_skill_0_, support_skill_1_, support_skill_2_})
	{
		elem->InitInventorySlot(this, true);
	}
}

void UInventoryWidget::UpdateSetBonusEffect()
{
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::AddToRewardContainer(UInventorySlot* slot_ptr)
{
	reward_container_->AddToRewardContainer(slot_ptr);
}

void UInventoryWidget::RemoveFromRewardContainer(UInventorySlot* slot_ptr)
{
	reward_container_->RemoveWidgetFromRewardContainer(slot_ptr);
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidget::NativeDestruct()
{
	UpdateInventoryData();
	Super::NativeDestruct();
}


void UInventoryWidget::UpdateInventoryData()
{
	rune_board_->UpdateRuneBoard();
	
}

void UInventoryWidget::OnHero_0_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(0);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_1_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(1);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_2_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(2);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_3_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(3);
	rune_board_->UpdateSetBonusEffect();
}