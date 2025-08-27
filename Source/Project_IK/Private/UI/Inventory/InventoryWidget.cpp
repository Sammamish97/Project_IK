/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Inventory/InventoryWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Inventory/HeroEquipBoardWidget.h"
#include "UI/RewardContainerWidget.h"
#include "UI/Inventory/RuneBoardWidget.h"
#include "UI/StatusWidget.h"
#include "UI/PopUps/BasicPopupWidget.h"
#include "UI/InventorySlots/ActiveSkillSlotWidget.h"
#include "UI/InventorySlots/PassiveSkillSlotWidget.h"
#include "UI/InventorySlots/RuneSlotWidget.h"
#include "UI/InventorySlots/WeaponSlotWidget.h"
#include "UI/PopUps/ActiveSkillPopupWidget.h"
#include "UI/PopUps/RunePopupWidget.h"
#include "UI/PopUps/SingleRunePopupWidget.h"
#include "UI/PopUps/WeaponPopupWidget.h"
#include "WorldSettings/IKHUD.h"


void UInventoryWidget::InitInventoryWidget(int32 available_passive_skill_amount, bool is_read_only)
{
	reward_container_->SetInventoryWidgetCache(this);
	rune_board_->SetInventoryWidget(this);
	rune_board_->LoadRuneBoardWidget();
	
	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	TArray hero_board_array =  {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_};

	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		elem->SetAvailablePassiveSkillAmount(available_passive_skill_amount);
	}
	
	for(int32 i = 0; i < 4; i++)
	{
		hero_board_array[i]->InitHeroEquipBoard(this, hero_type_array[i]);
		hero_board_array[i]->LoadHeroData();
	}
	
	hero_board_0_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_0_Board_Clicked);
	hero_board_1_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_1_Board_Clicked);
	hero_board_2_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_2_Board_Clicked);
	hero_board_3_->button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnHero_3_Board_Clicked);

	rune_switch_button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnRuneSwitchButtonClicked);
	status_switch_button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnStatusSwitchButtonClicked);

	confirm_button_->OnClicked.AddDynamic(this, &UInventoryWidget::OnConfirm);

	ToggleReadOnly(is_read_only);
	is_read_only_ = is_read_only;
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
	//1. 동일한 타입이 있는지 검사한다.
	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		if (elem->active_skill_slot_->GetStoredActiveSkillData().type_ == type)
		{
			return true;
		}
	}
	
	//2. 자신과 type은 동일하지만 등급이 다른 스킬이 있는지 검사한다.
	EActiveSkillType opposite_type = GetOppositeActiveSkillType(type);
	for (const auto& elem : {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		if (elem->active_skill_slot_->GetStoredActiveSkillData().type_ == opposite_type)

		{
			return true;
		}
	}
	return false;
}

bool UInventoryWidget::CheckDuplicatedPassiveSkill(EHeroType hero_type, EPassiveSkillType type)
{
	TObjectPtr<UHeroEquipBoardWidget> target_widget = nullptr;
	switch (hero_type)
	{
		case EHeroType::Hero1:
			target_widget = hero_board_0_;
			break;
		case EHeroType::Hero2:
			target_widget = hero_board_1_;
			break;
		case EHeroType::Hero3:
			target_widget = hero_board_2_;
			break;
		case EHeroType::Hero4:
			target_widget = hero_board_3_;
			break;
	}
	return target_widget->CheckDuplicatedPassiveSkill(type);
}

void UInventoryWidget::LoadSelectedRewards(const FWrapperEquipmentData& rewards)
{
	reward_container_->LoadSelectedRewards(rewards);
}

void UInventoryWidget::NativeConstruct()
{
	OnHero_0_Board_Clicked();
	Super::NativeConstruct();
}

void UInventoryWidget::NativeDestruct()
{
	UpdateInventoryData();
	Super::NativeDestruct();
}

void UInventoryWidget::ToggleReadOnly(bool is_read_only)
{
	TArray hero_board_array = {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_};
	for (const auto& elem : hero_board_array)
	{
		elem->ToggleReadOnly(is_read_only);
	}
	rune_board_->ToggleReadOnly(is_read_only);
	if (is_read_only)
	{
		reward_container_->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		reward_container_->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInventoryWidget::CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
                                               const FWeaponStatusData& data)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, weapon_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UWeaponPopupWidget>(equip_popup_ptr_)->UpdateWeaponData(data);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UInventoryWidget::CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, active_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UActiveSkillPopupWidget>(equip_popup_ptr_)->UpdateCoolDown(cool_down);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UInventoryWidget::CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, passive_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UInventoryWidget::CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
	ERuneSetType rune_set_type)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, rune_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<USingleRunePopupWidget>(equip_popup_ptr_)->UpdateRuneData(rune_set_type, ERuneSetBonusType::Hexagon);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
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

//IKNOTICE: 이 함수를 통해 Rune을 Highlight하려 하면 안된다
//Rune은 int32로 override된 버전을 사용해야 한다. 
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
	
	default:
		last_highlighted_gear_type = EGearType::INVALID;
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
	//현재 룬 보드 정보 저장
	rune_board_->UpdateRuneBoard();

	//현재 장착된 영웅 장비 정보 저장
	for (const auto& elem :  {hero_board_0_, hero_board_1_, hero_board_2_, hero_board_3_})
	{
		elem->UpdateHeroData();
	}
}

void UInventoryWidget::OnHero_0_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero1);
	rune_board_->UpdateSetBonusEffect();
	status_board_->LoadStatusData(EHeroType::Hero1);
}

void UInventoryWidget::OnHero_1_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero2);
	rune_board_->UpdateSetBonusEffect();
	status_board_->LoadStatusData(EHeroType::Hero2);
}

void UInventoryWidget::OnHero_2_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero3);
	rune_board_->UpdateSetBonusEffect();
	status_board_->LoadStatusData(EHeroType::Hero3);
}

void UInventoryWidget::OnHero_3_Board_Clicked()
{
	rune_board_->UpdateRuneBoard();
	rune_board_->LoadRuneBoardWidget(EHeroType::Hero4);
	rune_board_->UpdateSetBonusEffect();
	status_board_->LoadStatusData(EHeroType::Hero4);
}

void UInventoryWidget::OnRuneSwitchButtonClicked()
{
	rune_status_switcher_->SetActiveWidget(rune_board_);
}

void UInventoryWidget::OnStatusSwitchButtonClicked()
{
	rune_status_switcher_->SetActiveWidget(status_board_);
}

void UInventoryWidget::OnConfirm()
{
	if (is_read_only_)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UpdateInventoryData();
		AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (hud)
		{
			hud->SwitchUIByState(ECombatEndState::ShowingMapUI);
		}
	}
}
