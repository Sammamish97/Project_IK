/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Source file for GameState.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Worldsettings/IKGameState.h"

#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Characters/HeroBase.h"
#include "Components/ActiveSkillMechanics.h"
#include "Components/EnergySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/SupportSkillData.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/ButtonBarWidget.h"
#include "UI/SkillPopupWidget.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"
#include "WorldSettings/IKPlayerController.h"

AIKGameState::AIKGameState()
	:Super::AGameStateBase()
{
	energy_system_component_ = CreateDefaultSubobject<UEnergySystemComponent>(TEXT("Energy System Component"));
}

void AIKGameState::BeginPlay()
{
	Super::BeginPlay();
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	auto level_transition_manager = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<ULevelTransitionSubsystem>();
	auto support_skill_data_ = level_transition_manager->GetSupportSkillData();
	for (int32 i = 0; i < 3; i++)
	{
		if (support_skill_data_[i].type_ != ESupportSkillType::INVALID)
		{
			equipped_support_skills_.Push(NewObject<USupportSkillBase>(this, support_skill_data_[i].support_skill_class_));
		}
		else
		{
			equipped_support_skills_.Push(nullptr);
		}
		support_skill_timers_.Push(FTimerHandle());
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
	equipped_support_skills_.Empty();
	support_skill_timers_.Empty();
	active_skill_timers_.Empty();
}

bool AIKGameState::UseEnergy(float amount)
{
	return energy_system_component_->UseEnergy(amount);
}

const TArray<TObjectPtr<USupportSkillBase>>& AIKGameState::GetSupportSkillPtr() const
{
	return equipped_support_skills_;
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
				Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->UpdatePopupData(casted_hero->GetActiveSkillItemData());
			}
		}
	}
}

void AIKGameState::ActivateSupportSkill(int32 support_num)
{
	if (equipped_support_skills_[support_num] != nullptr)
	{
		//IKTODO: 장착 유무를 여기서 확인해야 함.
		if (energy_system_component_->GetEnergy() > equipped_support_skills_[support_num]->GetCost())
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(support_skill_timers_[support_num]) == false)
			{
				player_controller_cache_->StartTargeting(equipped_support_skills_[support_num]->GetTargetParameters());
				selected_support_skill_ = equipped_support_skills_[support_num];;
				selected_support_num_ = support_num;
				selected_skill_type_ = ESelectedSkill::SupportSKill;
				Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->UpdatePopupData(equipped_support_skill_item_data_map_[support_num]);
			}
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
				GetWorld()->GetTimerManager().SetTimer(support_skill_timers_[selected_support_num_],selected_support_skill_->GetCoolTime(), false);
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
	Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->SetVisibility(ESlateVisibility::Hidden);
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
				ReduceCoolDown(hero_type,casted_hero->GetActiveSkill()->GetCoolTime() * percentage);
			}
		}
	}
}