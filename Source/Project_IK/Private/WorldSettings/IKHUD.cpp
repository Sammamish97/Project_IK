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
#include "Components/WidgetComponent.h"
#include "DataAssets/SupportSkillDataAsset.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Managers/CombatLevelResultManager.h"
#include "Managers/DataTableManager.h"
#include "Structs/HeroData.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

#include "Structs/ItemData.h"
#include "Structs/SpawnData.h"

#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/BuffContainer.h"

#include "UI/ButtonBarWidget.h"
#include "UI/EnemyHPUI.h"
#include "UI/SegmentedHPUI.h"
#include "UI/SkillButtonWidget.h"
#include "UI/SupportSkillButtonWidget.h"
#include "UI/HeroWidget.h"
#include "UI/PopUps/RunePopupWidget.h"

#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"

typedef TPair<ERuneSetType, TArray<int32>> RuneSetBonus;

#include "Managers/EnumCluster.h"

void AIKHUD::BeginPlay()
{
	UWorld* world = GetWorld();

	// Create the widget and add it to the viewport
	if (button_widget_class_)
	{
		button_bar_widget_ = CreateWidget<UButtonBarWidget>(world, button_widget_class_);
		BindHeroWidgetUI();
		BindSupportSkills();
		
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

void AIKHUD::BindEnemyHPUI(AActor* enemy)
{
	TObjectPtr<AIKGameState> ik_game_state = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	//적들의 Butt Widget와 Popup Widget을 연결.
	if (auto enemy_widget_component = Cast<AUnit>(enemy)->GetHPUIWidgetComponent())
	{
		if (auto enemy_hp_widget = Cast<UEnemyHPUI>(enemy_widget_component->GetWidget()))
		{
			enemy_hp_widget->InitEnemyHPUI(button_bar_widget_->GetBuffPopupWidget());
			ik_game_state->OnToggleDetailMode.AddDynamic(enemy_hp_widget, &UEnemyHPUI::OnToggleDetailMode);
		}
	}
}

void AIKHUD::BindHeroWidgetUI()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	UDelegateBridgeSubsystem* subsystem = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	UDataTableManager* data_table_cache = ik_instance->GetDataTableManager();
	auto game_mode =  Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	TMap<EHeroType, TArray<RuneSetBonus>> hero_rune_bonus_detail_map;
	
	auto hero_types = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	//각 EHerpType을 순회하며 HeroBase와 HeroWidget사이 필요한 delegate들을 bind. 
	for(auto cur_hero_type : hero_types)
	{
		auto cur_spawn_data = transition_system->GetSpawnData(cur_hero_type);
		if(cur_spawn_data.is_dead_ == false)
		{
			auto cur_hero = Cast<AHeroBase>(game_mode->GetHero(cur_hero_type));
			auto rune_pop_up_widget = button_bar_widget_->GetRunePopupWidget();
			auto cur_hero_data = data_table_cache->GetHeroData(cur_hero_type);
			
			button_bar_widget_->GetHeroWidget(cur_hero_type)->InitHeroWidget(button_bar_widget_->GetBuffPopupWidget(),
				cur_hero->GetRuneMechanics(), rune_pop_up_widget,
				cur_hero_type,
				cur_hero->GetCharacterStat()->GetMaxHitPoint(), cur_hero->GetCharacterStat()->GetHitPoint(),
				cur_hero_data);

			subsystem->BindOnHPOrShieldChanged(cur_hero->GetCharacterStat(), button_bar_widget_->GetHeroWidget(cur_hero_type)->GetHPWidget(), &USegmentedHPUI::UpdateWidget);
			
			if(cur_hero->HasActiveSkill())
			{
				auto cur_skill_button_widget = button_bar_widget_->GetActiveSkillButtonWidget(cur_hero_type);
				auto cur_active_skill_mechanics = cur_hero->GetActiveSkillMechanics();
				auto cur_skill_data = cur_active_skill_mechanics->GetEquippedActiveSkillData();
				auto cur_skill = cur_active_skill_mechanics->GetActiveSkill();
				
				cur_skill_button_widget->SetThumbnailTexture(cur_skill_data.item_data_.display_data_->thumbnail);
				cur_skill->on_activate_skill_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
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
	auto rune_pop_up_widget = button_bar_widget_->GetRunePopupWidget();
	rune_pop_up_widget->InitSetBonusDetails(hero_rune_bonus_detail_map);
}

void AIKHUD::BindSupportSkills()
{
	auto game_state = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	auto support_skill_data = game_state->GetSupportSkillData();
	auto support_skills = game_state->GetSupportSkills();
	for (int32 i = 0; i < 3; i++)
	{
		if (support_skills[i] != nullptr)
		{
			auto cur_skill_button_widget = button_bar_widget_->GetSupportSkillButtonWidget(i);
			cur_skill_button_widget->SetThumbnailTexture(support_skill_data[i]->display_data_->thumbnail);
			cur_skill_button_widget->SetSupportSkillCost(support_skills[i]->GetCost());
			support_skills[i]->on_activate_skill_.AddDynamic(cur_skill_button_widget, &USkillButtonWidget::OnSkillInvoked);
		}
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