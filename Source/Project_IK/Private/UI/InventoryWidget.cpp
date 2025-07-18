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


void UInventoryWidget::InitInventoryWidget(int32 available_support_skill_amount, int32 available_passive_skill_amount)
{
	reward_container_->SetInventoryWidgetCache(this);
	rune_board_->SetInventoryWidget(this);
	rune_board_->LoadRuneBoardWidget();
	
	TArray support_skill_widget_array =  {support_skill_0_, support_skill_1_, support_skill_2_};
	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	TArray hero_board_array =  {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_};

	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		elem->SetAvailablePassiveSkillAmount(available_passive_skill_amount);
	}

	for (int32 i = available_support_skill_amount; i < 3; ++i)
	{
		support_skill_widget_array[i]->SetIsEnabled(false);
	}
	
	for(int32 i = 0; i < 4; i++)
	{
		hero_board_array[i]->InitHeroEquipBoard(this, hero_type_array[i]);
		hero_board_array[i]->LoadHeroData();
	}

	ULevelTransitionSubsystem* subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();

	auto saved_support_skill_data = subsystem->GetSupportSkillData();
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

bool UInventoryWidget::CheckDuplicatedActiveSkill(EActiveSkillType type)
{
	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		if (elem->active_skill_slot_->GetStoredActiveSkillData().type_ == type)
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

void UInventoryWidget::CreatePopupWidget(const FItemData& item_data)
{
	if(equip_popup_class_ && equip_popup_ptr_ == nullptr)
	{
		equip_popup_ptr_ = CreateWidget<USkillPopupWidget>(this, equip_popup_class_);
		equip_popup_ptr_->UpdatePopupData(item_data);
		equip_popup_ptr_->AddToViewport();
		equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UInventoryWidget::SetPopupWidgetPos(FVector2D pos)
{
	if(equip_popup_ptr_)
	{
		equip_popup_ptr_->SetPositionInViewport(pos);
	}
}

void UInventoryWidget::RemovePopupWidget()
{
	if(equip_popup_ptr_)
	{
		equip_popup_ptr_->Destruct();
		equip_popup_ptr_->SetVisibility(ESlateVisibility::Hidden);
		equip_popup_ptr_ = nullptr;
	}
}

void UInventoryWidget::SetHighlightVisibility(EGearType type, ESlateVisibility visibility)
{
	last_highlighted_gear_type = type;
	switch (type)
	{
	case EGearType::Weapon:
		{
			for(const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
			{
				elem->weapon_slot_->SetHighlightImageVisibility(visibility);
			}
		}
		break;

	case EGearType::ActiveSkill:
		for(const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
		{
			elem->active_skill_slot_->SetHighlightImageVisibility(visibility);
		}
		break;

	case EGearType::PassiveSkill:
		for(const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
		{
			for (const auto& passive_skill_widget : {elem->passive_skill_1_slot_, elem->passive_skill_2_slot_, elem->passive_skill_3_slot_})
			{
				if (passive_skill_widget->GetIsEnabled())
				{
					passive_skill_widget->SetHighlightImageVisibility(visibility);
				}
			}
		}
		break;

	case EGearType::SupportSkill:
		for(const auto& elem : {support_skill_0_, support_skill_1_, support_skill_2_})
		{
			if (elem->GetIsEnabled())
			{
				elem->SetHighlightImageVisibility(visibility);
			}
		}
		break;
		
	default:
		last_highlighted_gear_type = EGearType::INVALID;
		//IKTODO: 이 함수를 통해 Rune을 Highlight하려 하면 안된다
		//Rune은 int32로 override된 버전을 사용해야 한다. 
	}
}

void UInventoryWidget::SetHighlightVisibility(int32 rune_idx, ESlateVisibility visibility)
{
	last_highlighted_gear_type = EGearType::Rune;
	rune_board_->GetRuneSlotWidget(rune_idx)->SetHighlightImageVisibility(visibility);
}

void UInventoryWidget::RemoveHighlight()
{
	if(last_highlighted_gear_type == EGearType::Rune)
	{
		for(int32 i = 0; i < 6; ++i)
		{
			SetHighlightVisibility(i, ESlateVisibility::Hidden);
		}
	}
	else
	{
		SetHighlightVisibility(last_highlighted_gear_type, ESlateVisibility::Hidden);
	}
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
