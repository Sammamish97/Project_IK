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
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/HeroEquipBoardWidget.h"
#include "UI/RewardContainerWidget.h"
#include "UI/RuneBoardWidget.h"
#include "UI/InventorySlots/ActiveSkillSlotWidget.h"
#include "UI/InventorySlots/SupportSkillSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKHUD.h"

void UInventoryWidget::InitInventoryWidget()
{
	reward_container_->SetInventoryWidgetCache(this);
	rune_board_->SetInventoryWidget(this);
	rune_board_->LoadRuneBoardWidget();

	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	TArray hero_board_array =  {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_}; 
	
	for(int32 i = 0; i < 4; i++)
	{
		hero_board_array[i]->InitHeroEquipBoard(this, hero_type_array[i]);
		hero_board_array[i]->LoadHeroData();
	}

	ULevelTransitionSubsystem* subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();

	auto saved_support_skill_data = subsystem->GetSupportSkillData();
	TArray support_skill_widget_array =  {support_skill_0_, support_skill_1_, support_skill_2_};
	for(int32 i = 0; i < 3; ++i)
	{
		support_skill_widget_array[i]->InitInventorySlot(this, true);
		support_skill_widget_array[i]->SetSupportSkillSlotData(saved_support_skill_data[i]);
	}
	
	hero_board_0_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_0_Board_Clicked);
	hero_board_1_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_1_Board_Clicked);
	hero_board_2_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_2_Board_Clicked);
	hero_board_3_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_3_Board_Clicked);

	confirm_button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnConfirm);
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

bool UInventoryWidget::CheckDuplicatedActiveSkill(const FActiveSkillData& skill_data)
{
	//1. 동일한 타입이 있는지 검사한다.
	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		if (elem->active_skill_slot_->GetStoredActiveSkillData().type_ == skill_data.type_)
		{
			return true;
		}
	}
	
	//2. 자신과 type은 동일하지만 등급이 다른 스킬이 있는지 검사한다.

	EActiveSkillType opposite_type = GetOppositeActiveSkillType(skill_data.type_);
	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		if (elem->active_skill_slot_->GetStoredActiveSkillData().type_ == opposite_type)
		{
			return true;
		}
	}
	return false;
}

bool UInventoryWidget::CheckDuplicatedSupportSkill(ESupportSkillType type)
{
	for (const auto& elem : {support_skill_0_, support_skill_1_, support_skill_2_})
	{
		if (elem->GetStoredSupportSkillData().type_ == type)
		{
			return true;
		}
	}
	return false;
}

void UInventoryWidget::LoadSelectedRewards(const FWrapperEquipmentData& rewards)
{
	reward_container_->LoadSelectedRewards(rewards);
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
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero1);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_1_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero2);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_2_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero3);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnHero_3_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero4);
	rune_board_->UpdateSetBonusEffect();
}

void UInventoryWidget::OnConfirm()
{
	//현재 룬 보드 정보 저장
	rune_board_->UpdateRuneBoard();

	//현재 장착된 영웅 장비 정보 저장
	for (const auto& elem :  {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		elem->UpdateHeroData();
	}

	//현재 장착된 서포트 스킬 정보 저장.
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	TMap<int32, FSupportSkillData> support_skill_map;
	support_skill_map.Add(0, support_skill_0_->GetStoredSupportSkillData());
	support_skill_map.Add(1, support_skill_1_->GetStoredSupportSkillData());
	support_skill_map.Add(2, support_skill_2_->GetStoredSupportSkillData());
	transition_system->UpdateSupportSkillData(support_skill_map);

	//지도 UI 팝업
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		hud->SwitchUIByState(ECombatEndState::ShowingMapUI);
	}
}
