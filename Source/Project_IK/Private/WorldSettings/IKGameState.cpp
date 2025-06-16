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
#include "Components/EnergySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/SupportSkillData.h"
#include "UI/ButtonBarWidget.h"
#include "UI/SkillPopupWidget.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"
#include "WorldSettings/IKPlayerController.h"

AIKGameState::AIKGameState()
	:Super::AGameStateBase()
{
	energy_system_component_ = CreateDefaultSubobject<UEnergySystemComponent>(TEXT("Energy System Component"));
	support_skill_data_.Init(FSupportSkillData(), 3);
	equipped_support_skills_.Init(TObjectPtr<USupportSkillBase>(), 3);
}

void AIKGameState::BeginPlay()
{
	Super::BeginPlay();
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	for (int32 i = 0; i < 3; i++)
	{
		if (support_skill_data_[i].type_ != ESupportSkillType::INVALID)
		{
			equipped_support_skills_[i] = NewObject<USupportSkillBase>(this, support_skill_data_[i].support_skill_class_);
			support_skill_timers_.Add(i, FTimerHandle{});
		}
	}

	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	for (const auto& elem : game_mode_cache->GetHeroContainer())
	{
		if (elem != nullptr)
		{
			active_skill_timers_.Add(Cast<AHeroBase>(elem)->GetHeroType(), FTimerHandle{});
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

const TArray<FSupportSkillData>& AIKGameState::GetSupportSkillData() const
{
	return support_skill_data_;
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
				player_controller_cache_->StartTargeting(casted_hero->GetActiveSkillTargetParameters());
				selected_skill_ = casted_hero->GetActiveSkill();
				selected_hero_type_ = hero_type;
				Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->UpdateSkillPopupData(selected_hero_type_);
			}
		}
	}
}

void AIKGameState::ActivateSupportSkill(int32 support_num)
{
	if (equipped_support_skills_.IsValidIndex(support_num))
	{
		if (energy_system_component_->GetEnergy() > equipped_support_skills_[support_num]->GetCost())
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(support_skill_timers_[support_num]) == false)
			{
				player_controller_cache_->StartTargeting(equipped_support_skills_[support_num]->GetTargetParameters());
				selected_skill_ = equipped_support_skills_[support_num];
				selected_support_num_ = support_num;
				Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->UpdateSkillPopupData(selected_support_num_);
			}
		}
	}
}

bool AIKGameState::OnDecide(const FTargetResult& result)
{
	if (selected_skill_)
	{
		if (selected_skill_.IsA(USupportSkillBase::StaticClass()))
		{
			energy_system_component_->UseEnergy(Cast<USupportSkillBase>(selected_skill_)->GetCost());
			GetWorld()->GetTimerManager().SetTimer(support_skill_timers_[selected_support_num_],selected_skill_->GetCoolTime(), false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(active_skill_timers_[selected_hero_type_],selected_skill_->GetCoolTime(), false);
		}
		auto next_targeting = selected_skill_->ActivateSkill(result);
		if (next_targeting.IsSet())
		{
			player_controller_cache_->StartTargeting(next_targeting.GetValue());
		}
		else
		{
			ClearTargetingState();
		}
		return true;
	}
	return false;
}

void AIKGameState::ClearTargetingState()
{
	selected_skill_ = nullptr;
	selected_hero_type_ = EHeroType::INVALID;
	selected_support_num_ = -1;
	Cast<AIKHUD>(player_controller_cache_->GetHUD())->GetButtonBarWidget()->GetSkillPopupWidget()->SetVisibility(ESlateVisibility::Hidden);
}
