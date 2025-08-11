/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Source file for GameState.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Worldsettings/IKGameState.h"

#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Characters/HeroBase.h"

#include "Components/ActiveSkillMechanics.h"
#include "Components/CharacterStatComponent.h"
#include "Components/EnergySystemComponent.h"

#include "DataAssets/SupportSkillDataAsset.h"
#include "Kismet/GameplayStatics.h"

#include "UI/ButtonBarWidget.h"
#include "UI/PopUps/BasicPopupWidget.h"
#include "UI/PopUps/ActiveSkillPopupWidget.h"
#include "UI/PopUps/SupportSkillPopupWidget.h"

#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"
#include "WorldSettings/IKPlayerController.h"

#include "Managers/TextManager.h"


AIKGameState::AIKGameState()
	:Super::AGameStateBase()
{
	energy_system_component_ = CreateDefaultSubobject<UEnergySystemComponent>(TEXT("Energy System Component"));
}

void AIKGameState::BeginPlay()
{
	Super::BeginPlay();
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
	
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	support_skill_data_ = {relocation_data_, set_attack_target_data_, maintain_data_};

	for (int32 i = 0; i < 3; i++)
	{
		support_skills_.Push(NewObject<USupportSkillBase>(this,support_skill_data_[i]->support_skill_class_));
	}

	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	for (const auto& elem : game_mode_cache->GetHeroContainer())
	{
		if (auto cur_hero_ptr = elem)
		{
			active_skill_timers_.Add(Cast<AHeroBase>(cur_hero_ptr)->GetHeroType(), FTimerHandle{});
		}
	}
}

void AIKGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	support_skills_.Empty();
	active_skill_timers_.Empty();
}

bool AIKGameState::UseEnergy(float amount)
{
	return energy_system_component_->UseEnergy(amount);
}

UEnergySystemComponent* AIKGameState::GetEnergySystemComponent()
{
	return energy_system_component_;
}

void AIKGameState::ActivateSkillTargeting(EHeroType hero_type)
{
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (auto selected_hero = game_mode_cache->GetHero(hero_type))
	{
		AHeroBase* casted_hero = Cast<AHeroBase>(selected_hero);
		if (casted_hero->HasActiveSkill())
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(active_skill_timers_[casted_hero->GetHeroType()]) == false)
			{
				player_controller_cache_->StartTargeting(casted_hero->GetActiveSkillTargetParameters(), casted_hero);
				selected_active_skill_mechanics_ = casted_hero->GetActiveSkillMechanics();
				selected_hero_type_ = hero_type;
				selected_skill_type_ = ESelectedSkill::ActiveSkill;
				
				FText name = text_manager_cache_->GetNameText(casted_hero->GetActiveSkillItemData().display_data_->text_key_);
				auto active_skill_data = casted_hero->GetActiveSkillMechanics()->GetEquippedActiveSkillData();
				auto active_skill_popup = Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetActiveSkillPopupWidget();
				active_skill_popup->UpdatePopupData(
					casted_hero->GetActiveSkillItemData().display_data_->thumbnail,
					name,
					active_skill_data.BuildDetailText(GetWorld(), casted_hero->GetCharacterStat()->GetCharacterData()));
				active_skill_popup->UpdateCoolDown(active_skill_data.cool_time_);
			}
		}
	}
}

void AIKGameState::ActivateSupportSkill(int32 support_num)
{
	if (support_skills_[support_num] != nullptr)
	{
		if (energy_system_component_->GetEnergy() > support_skills_[support_num]->GetCost())
		{
			
			player_controller_cache_->StartTargeting(support_skills_[support_num]->GetTargetParameters());
			selected_support_skill_ = support_skills_[support_num];
			selected_support_num_ = support_num;
			selected_skill_type_ = ESelectedSkill::SupportSKill;
			
			FText name = text_manager_cache_->GetNameText(support_skill_data_[support_num]->display_data_->text_key_);
			FText detail = text_manager_cache_->GetDetailText(support_skill_data_[support_num]->display_data_->text_key_);

			auto support_skill_popup =Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSupportSkillPopupWidget();
			support_skill_popup->UpdatePopupData(
				support_skill_data_[support_num]->display_data_->thumbnail,
				name,
				detail);
			support_skill_popup->UpdateCost(support_skill_data_[support_num]->cost_);
		}
	}
}

bool AIKGameState::OnDecide(const FTargetResult& result)
{
	switch (selected_skill_type_)
	{
		case ESelectedSkill::ActiveSkill:
			{
				GetWorld()->GetTimerManager().SetTimer(active_skill_timers_[selected_hero_type_],selected_active_skill_mechanics_->GetCooltime(), false);
				selected_active_skill_mechanics_->ActivateSkill(result);
				ClearTargetingState();
			}
			break;
		case ESelectedSkill::SupportSKill:
			{
				energy_system_component_->UseEnergy(Cast<USupportSkillBase>(selected_support_skill_)->GetCost());
				if (selected_support_skill_->ActivateSkill(result))
				{			
					ClearTargetingState();
				}
			}
			break;
	}
	return false;
}

void AIKGameState::ClearTargetingState()
{
	if (selected_active_skill_mechanics_)
	{
		if (selected_active_skill_mechanics_->HasActiveSkill())
		{
			selected_active_skill_mechanics_->GetActiveSkill()->ResetSkill();
			selected_active_skill_mechanics_ = nullptr;
		}
	}
	if(selected_support_skill_)
	{
		selected_support_skill_->ResetSkill();
		selected_support_skill_ = nullptr;
	}
	selected_skill_type_ = ESelectedSkill::INVALID;
	selected_hero_type_ = EHeroType::INVALID;
	selected_support_num_ = -1;
	Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->ClearPopupWidget();
}

void AIKGameState::ReduceCoolDown(EHeroType hero_type, float amount)
{
	float left_cool_down = 0.0f;
	if (active_skill_timers_.Contains(hero_type))
	{
		float remaining_time = GetWorld()->GetTimerManager().GetTimerRemaining(active_skill_timers_[hero_type]);
		if (remaining_time < amount)
		{
			left_cool_down = 0.f;
			GetWorld()->GetTimerManager().ClearTimer(active_skill_timers_[hero_type]);
		}
		else
		{
			left_cool_down = remaining_time - amount;
			GetWorld()->GetTimerManager().SetTimer(active_skill_timers_[hero_type],left_cool_down, false);
		}
	}
	
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (auto selected_hero = game_mode_cache->GetHero(hero_type))
	{
		AHeroBase* casted_hero = Cast<AHeroBase>(selected_hero);
		if (casted_hero->HasActiveSkill())
		{
			auto skill = casted_hero->GetActiveSkill();
			skill->UpdateCoolDown(left_cool_down);
		}
	}
	
}

void AIKGameState::ReduceCoolDownPercentage(EHeroType hero_type, float percentage)
{
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (active_skill_timers_.Contains(hero_type))
	{
		if (auto selected_hero = game_mode_cache->GetHero(hero_type))
		{
			AHeroBase* casted_hero = Cast<AHeroBase>(selected_hero);
			if (casted_hero->HasActiveSkill())
			{
				ReduceCoolDown(hero_type,Cast<UActiveSkillBase>(casted_hero->GetActiveSkill())->GetCoolTime() * percentage);
			}
		}
	}
}

void AIKGameState::ToggleFocusMode()
{
	on_focus_mode_ = !on_focus_mode_;
	OnToggleDetailMode.Broadcast(on_focus_mode_);
}

const TArray<TObjectPtr<USupportSkillDataAsset>>& AIKGameState::GetSupportSkillData()
{
	return support_skill_data_;
}

const TArray<TObjectPtr<USupportSkillBase>>& AIKGameState::GetSupportSkills()
{
	return support_skills_;
}
