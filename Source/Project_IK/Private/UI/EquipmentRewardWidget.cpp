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
#include "UI/RewardSelectWidget.h"
#include "Components/UniformGridPanel.h"
#include "Managers/InventoryManager.h"

#include "Subsystems/PerkModifierSubsystem.h"
#include "UI/PopUps/ActiveSkillPopupWidget.h"
#include "UI/PopUps/BasicPopupWidget.h"
#include "UI/PopUps/SingleRunePopupWidget.h"
#include "UI/PopUps/WeaponPopupWidget.h"

void UEquipmentRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	 const auto& equipments_ = game_instance->GetDataTableManager()->GetUniqueEquipmentDataRandomly(
	 	game_instance->GetSubsystem<UPerkModifierSubsystem>()->GetCombatEndEquipmentRewardNumCandidates()
	 );
	
	 max_choice_ = game_instance->GetSubsystem<UPerkModifierSubsystem>()->GetCombatEndEquipmentRewardMaxChoice();
	
	 for (const auto& elem : equipments_.active_skills_)
	 {
	 	auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
	 	new_widget->SetRewardData(elem);
	 	reward_widgets_.Push(new_widget);
	 }
	 for (const auto& elem : equipments_.passive_skills_)
	 {
	 	auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
	 	new_widget->SetRewardData(elem);
	 	reward_widgets_.Push(new_widget);
	 }
	 for (const auto& elem : equipments_.weapons_)
	 {
	 	auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
	 	new_widget->SetRewardData(elem);
	 	reward_widgets_.Push(new_widget);
	 }
	 for (const auto& elem : equipments_.runes_)
	 {
	 	auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
	 	new_widget->SetRewardData(elem);
	 	reward_widgets_.Push(new_widget);
	 }
	
	 const int32 width_size = 4;
	 int32 counter = 0;
	 for (const auto& elem : reward_widgets_)
	 {
	 	elem->SetEquipmentWidgetCache(this);
	 	reward_container_->AddChildToUniformGrid(elem, counter / width_size, counter % width_size);
	 	counter += 1;
	 }

	confirm_button_->OnClicked.AddDynamic(this, &UEquipmentRewardWidget::OnConfirmButtonClicked);
}

void UEquipmentRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	reward_widgets_.Empty();
	confirm_button_->OnClicked.Clear();
}

void UEquipmentRewardWidget::CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
											   const FWeaponStatusData& data)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, weapon_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UWeaponPopupWidget>(equip_popup_ptr_)->UpdateWeaponData(data);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEquipmentRewardWidget::CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, active_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<UActiveSkillPopupWidget>(equip_popup_ptr_)->UpdateCoolDown(cool_down);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEquipmentRewardWidget::CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, passive_skill_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEquipmentRewardWidget::CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail,
	ERuneSetType rune_set_type)
{
	equip_popup_ptr_ = CreateWidget<UBasicPopupWidget>(this, rune_popup_class_);
	equip_popup_ptr_->UpdatePopupData(thumbnail, name, detail);
	Cast<USingleRunePopupWidget>(equip_popup_ptr_)->UpdateRuneData(rune_set_type, ERuneSetBonusType::Hexagon);
	equip_popup_ptr_->AddToViewport();
	equip_popup_ptr_->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UEquipmentRewardWidget::SetPopupWidgetPos(FVector2D pos)
{
	if(equip_popup_ptr_)
	{
		equip_popup_ptr_->SetPositionInViewport(pos, false);
	}
}

void UEquipmentRewardWidget::RemovePopupWidget()
{
	if(equip_popup_ptr_)
	{
		equip_popup_ptr_->Destruct();
		equip_popup_ptr_->SetVisibility(ESlateVisibility::Hidden);
		equip_popup_ptr_ = nullptr;
	}
}

void UEquipmentRewardWidget::IncreaseSelectedCounter()
{
	selected_amount_ = FMath::Min(selected_amount_ + 1, max_choice_);
	//만약 선택 한계에 도달했다면, 선택되지 못한 widget들을 disable 시킨다.
	if (selected_amount_ >= max_choice_)
	{
		for (auto& elem : reward_widgets_)
		{
			if (elem->GetIsChecked() == false)
			{
				elem->SetIsEnabled(false);
			}
		}
	}
}

void UEquipmentRewardWidget::DecreaseSelectedCounter()
{
	selected_amount_ = FMath::Max(selected_amount_ - 1, 0);
	//모든 widget을 enable 시킨다.
	for (auto& elem : reward_widgets_)
	{
		elem->SetIsEnabled(true);
	}	
}

void UEquipmentRewardWidget::OnConfirmButtonClicked()
{
	FWrapperEquipmentData selected_reward_data;
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		for (const auto& elem : reward_widgets_)
		{
			if (elem->GetIsChecked())
			{
				const auto& reward_data = elem->GetRewardData();
				switch (reward_data.gear_type_)
				{
				case EGearType::Weapon:
					selected_reward_data.weapons_.Push(reward_data.weapon_data_);
					break;
				case EGearType::ActiveSkill:
					selected_reward_data.active_skills_.Push(reward_data.active_skill_data_);
					break;
				case EGearType::PassiveSkill:
					selected_reward_data.passive_skills_.Push(reward_data.passive_skill_data_);
					break;
				case EGearType::Rune:
					selected_reward_data.runes_.Push(reward_data.rune_data_);
					break;
				default:
					break;
					//IKTODO: 예외처리
				}
			}
		}

		UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		hud->SwitchUIByState(ECombatEndState::ShowingInventoryUI);

		game_instance->GetInventoryManager()->OpenInventoryWidgetReward(selected_reward_data,
			[&]() 
			{
				AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
				if (hud)
				{
					hud->SwitchUIByState(ECombatEndState::ShowingMapUI);
				}
			});
	}
}
