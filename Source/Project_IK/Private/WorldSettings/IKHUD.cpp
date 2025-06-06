/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/IKHUD.h"

#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Managers/CombatLevelResultManager.h"
#include "UI/ButtonBarWidget.h"
#include "UI/InventoryWidget.h"
#include "UI/SkillButtonWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameState.h"
#include "WorldSettings/IKPlayerController.h"

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	// Create the widget and add it to the viewport
	if (button_widget_class_)
	{
		button_widget_ = CreateWidget<UButtonBarWidget>(world, button_widget_class_);
		
		auto game_state = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
		auto equipped_support_data = game_state->GetSupportSkillData();
		auto equipped_support_skills = game_state->GetSupportSkillPtr();
		for (int32 i = 0; i < 3; i++)
		{
			if (equipped_support_skills[i] != nullptr)
			{
				auto cur_skill_button_widget = GetSkillButtonWidget(i);
                cur_skill_button_widget->SetThumbnailTexture(equipped_support_data[i].thumbnail);
				equipped_support_skills[i]->on_decide_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
			}
		}
		if (button_widget_)
		{
			button_widget_->AddToViewport();
		}
	}

	combat_level_result_manager_ = NewObject<UCombatLevelResultManager>(world, combat_level_widget_class_);
	if (combat_level_result_manager_)
	{
		combat_level_result_manager_->InitializeUI();
	}

	if(inventory_widget_class_)
	{
		inventory_widget_ = CreateWidget<UInventoryWidget>(GetWorld(), inventory_widget_class_);
		if(inventory_widget_)
		{
			auto ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if(ik_instance)
			{
				inventory_widget_->InitInventoryWidget(ik_instance->GetInventoryManager());
				inventory_widget_->AddToViewport();
				inventory_widget_->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void AIKHUD::DisplayCombatResult(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	if (combat_level_result_manager_)
	{
		combat_level_result_manager_->DisplayCombatResult(heroes, damage_map);
	}
}

void AIKHUD::SwitchUIByState(ECombatEndState state)
{
	if (combat_level_result_manager_)
	{
		combat_level_result_manager_->SwitchUIByState(state);
	}
}

void AIKHUD::SilenceSkill(AActor* character)
{
	if (button_widget_)
	{
		button_widget_->SilenceSkill(character);
	}
}

void AIKHUD::UnsilenceSkill(AActor* character)
{
	if (button_widget_)
	{
		button_widget_->UnsilenceSkill(character);
	}
}

void AIKHUD::ToggleInventory()
{
	if (inventory_widget_->GetVisibility() == ESlateVisibility::Hidden)
	{
		inventory_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		inventory_widget_->SetVisibility(ESlateVisibility::Hidden);
	}
}

USkillButtonWidget* AIKHUD::GetSkillButtonWidget(int32 idx)
{
	return button_widget_->GetSkillButtonWidget(idx);
}
