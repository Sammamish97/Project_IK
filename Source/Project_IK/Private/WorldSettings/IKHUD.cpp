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
#include "Components/RuneMechanics.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Managers/CombatLevelResultManager.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

#include "Structs/ItemData.h"
#include "Structs/SpawnData.h"

#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/BuffContainer.h"

#include "UI/ButtonBarWidget.h"
#include "UI/SegmentedHPUI.h"
#include "UI/RunePopupWidget.h"
#include "UI/SkillButtonWidget.h"
#include "UI/SkillPopupWidget.h"
#include "UI/SupportSkillButtonWidget.h"
#include "UI/UnitWidget.h"

#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

typedef TPair<ERuneSetType, TArray<int32>> RuneSetBonus;

#include "Managers/EnumCluster.h"

void AIKHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();

	// Create the widget and add it to the viewport
	if (button_widget_class_)
	{
		button_bar_widget_ = CreateWidget<UButtonBarWidget>(world, button_widget_class_);
		
		//액티브 스킬 UI에 썸네일을 Bind.
		auto game_mode =  Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		auto hero_types = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
		TMap<EHeroType, TArray<RuneSetBonus>> hero_rune_bonus_detail_map;

		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
		
		for(auto cur_hero_type : hero_types)
		{
			auto cur_spawn_data = transition_system->GetSpawnData(cur_hero_type);
			if(cur_spawn_data.is_dead_ == false)
			{
				auto cur_hero = Cast<AHeroBase>(game_mode->GetHero(cur_hero_type));
				if(cur_hero->HasActiveSkill())
				{
					auto cur_skill_button_widget = button_bar_widget_->GetActiveSkillButtonWidget(cur_hero_type);
					auto cur_active_skill_mechanics = cur_hero->GetActiveSkillMechanics();
					auto cur_skill_data = cur_active_skill_mechanics->GetEquippedActiveSkillData();
					auto cur_skill = cur_active_skill_mechanics->GetActiveSkill();
					
					cur_skill_button_widget->SetThumbnailTexture(cur_skill_data.item_data_.thumbnail);
					cur_skill->on_activate_skill_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
					
					subsystem->BindOnHPOrShieldChanged(cur_hero->GetCharacterStat(), button_bar_widget_->GetHeroWidget(cur_hero_type)->GetHPWidget(), &USegmentedHPUI::UpdateWidget);
					button_bar_widget_->GetHeroWidget(cur_hero_type)->InitHeroWidget(button_bar_widget_->GetBuffPopupWidget(),
						cur_hero->GetRuneMechanics(), button_bar_widget_->GetRunePopupWidget(),
						cur_hero_type, cur_hero->GetHeroBaseColor_1(), cur_hero->GetHeroBaseColor_2(),
						cur_hero->GetCharacterStat()->GetMaxHitPoint(), cur_hero->GetCharacterStat()->GetHitPoint());
				}
				else
				{
					auto cur_skill_button_widget = button_bar_widget_->GetActiveSkillButtonWidget(cur_hero_type);
					//IKTODO: 이후 nullptr에서 Empty Icon같은 걸로 바꿔야 함.
					cur_skill_button_widget->SetThumbnailTexture(nullptr);
				}
				cur_hero->OnApplyBuff.AddDynamic(button_bar_widget_->GetHeroWidget(cur_hero_type)->GetBuffContainer(), &UBuffContainer::EnqueueBuff);
				cur_hero->OnBuffExpired.AddDynamic(button_bar_widget_->GetHeroWidget(cur_hero_type)->GetBuffContainer(), &UBuffContainer::UpdateQueue);
				
				hero_rune_bonus_detail_map.Add(cur_hero_type, cur_hero->GetRuneMechanics()->GetSetBonusData());
			}
			else
			{
				//IKTODO: 만약 죽은 영웅이라면?
			}
		}

		//서포트 스킬 UI에 썸네일과 Cost를 Bind.
		auto game_state = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
		auto equipped_support_skills = game_state->GetSupportSkillPtr();
		auto equipped_support_data = transition_system->GetSupportSkillData();
		for (int32 i = 0; i < 3; i++)
		{
			if (equipped_support_skills[i] != nullptr)
			{
				auto cur_skill_button_widget = button_bar_widget_->GetSupportSkillButtonWidget(i);
				cur_skill_button_widget->SetThumbnailTexture(equipped_support_data[i].item_data_.thumbnail);
				cur_skill_button_widget->SetSupportSkillCost(equipped_support_skills[i]->GetCost());
				equipped_support_skills[i]->on_activate_skill_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
			}
		}
		
		auto rune_pop_up_widget = button_bar_widget_->GetRunePopupWidget();
		rune_pop_up_widget->InitSetBonusDetails(hero_rune_bonus_detail_map);
		
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
}

void AIKHUD::DisplayCombatResult(const TMap<EHeroType, float>& damage_map)
{
	if (combat_level_result_manager_)
	{
		combat_level_result_manager_->DisplayCombatResult(damage_map);
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