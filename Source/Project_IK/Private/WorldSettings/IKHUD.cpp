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
#include "Characters/HeroBase.h"
#include "Components/ActiveSkillMechanics.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Managers/CombatLevelResultManager.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "UI/ButtonBarWidget.h"
#include "UI/SegmentedHPUI.h"
#include "UI/InventoryWidget.h"
#include "UI/SkillButtonWidget.h"
#include "UI/UnitWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();

	// Create the widget and add it to the viewport
	if (button_widget_class_)
	{
		button_bar_widget_ = CreateWidget<UButtonBarWidget>(world, button_widget_class_);
		
		auto game_state = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
		auto equipped_support_data = game_state->GetSupportSkillData();
		auto equipped_support_skills = game_state->GetSupportSkillPtr();
		for (int32 i = 0; i < 3; i++)
		{
			if (equipped_support_skills[i] != nullptr)
			{
				auto cur_skill_button_widget = button_bar_widget_->GetSupportSkillButtonWidget(i);
                cur_skill_button_widget->SetThumbnailTexture(equipped_support_data[i].thumbnail);
				equipped_support_skills[i]->on_decide_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
			}
		}
		
		auto game_mode =  Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		auto hero_types = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
		for(auto elem :hero_types)
		{
			auto cur_hero = Cast<AHeroBase>(game_mode->GetHero(elem));
			if(cur_hero->HasActiveSkill())
			{
				auto cur_skill_button_widget = button_bar_widget_->GetActiveSkillButtonWidget(elem);
				auto cur_active_skill_mechanics = cur_hero->GetActiveSkillMechanics();
				cur_skill_button_widget->SetThumbnailTexture(cur_active_skill_mechanics->GetEquippedActiveSkillData().thumbnail);
				cur_active_skill_mechanics->on_active_skill_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
				
				subsystem->BindOnHPOrShieldChanged(cur_hero->GetCharacterStat(), button_bar_widget_->GetHeroWidget(cur_hero->GetHeroType())->GetHPWidget(), &USegmentedHPUI::UpdateWidget);
				button_bar_widget_->GetHeroWidget(cur_hero->GetHeroType())->InitHeroWidget(cur_hero->GetRuneMechanics(), cur_hero->GetCharacterStat()->GetMaxHitPoint(), cur_hero->GetCharacterStat()->GetHitPoint());
			}
			else
			{
				auto cur_skill_button_widget = button_bar_widget_->GetActiveSkillButtonWidget(elem);
				//IKTODO: 이후 nullptr에서 Empty Icon같은 걸로 바꿔야 함.
				cur_skill_button_widget->SetThumbnailTexture(nullptr);
			}
			subsystem->BindOnCrowdControlChanged(cur_hero->GetCCComponent(), button_bar_widget_->GetHeroWidget(cur_hero->GetHeroType()), &UHeroWidget::UpdateAppliedCCs);
			subsystem->BindOnBuffChanged(cur_hero->GetCharacterStat(), button_bar_widget_->GetHeroWidget(cur_hero->GetHeroType()), &UHeroWidget::UpdateAppliedBuffs);
		}
		
		if (button_bar_widget_)
		{
			button_bar_widget_->AddToViewport();
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

UButtonBarWidget* AIKHUD::GetButtonBarWidget()
{
	return button_bar_widget_;
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
