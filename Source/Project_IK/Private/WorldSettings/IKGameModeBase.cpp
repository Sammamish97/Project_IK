/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKGameModeBase.h"

#include "AI/MeleeAIController.h"
#include "Kismet/GameplayStatics.h"

#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKPlayerController.h"
#include "Managers/TimeDilationManager.h"
#include "Managers/EnemySpawnerManager.h"

#include "WorldSettings/IKHUD.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Components/PassiveSkillMechanics.h"
#include "Components/TargetingComponent.h"
#include "Environments/SpawnMarker.h"
#include "Structs/SpawnData.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/Map/IKMaps.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Managers/DataTableManager.h"

#include "Subsystems/PerkModifierSubsystem.h"
#include "Managers/InventoryManager.h"

#include "Subsystems/AudioManagerSubsystem.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
}

void AIKGameModeBase::StartPlay()
{
	Super::StartPlay();


	AIKHUD* hud = Cast<AIKHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (hud)
	{
		hud->InitializeHUDAfterGameModeInit();
	}

	for (auto& elem : heroes_)
	{
		if (AHeroBase* hero = Cast<AHeroBase>(elem))
		{
			hero->GetPassiveSkillMechanics()->InitPassiveSkill();
			GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->ApplyBuff(hero);
		}
	}
	// SpawnEnemies function should be called after SpawnHeroes has been called.
	SpawnEnemies();
}

void AIKGameModeBase::BeginPlay()
{

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::CombatAmbient);

	hero_spawn_position_ = FVector();
	time_dilation_manager_ = NewObject<UTimeDilationManager>(this);



	SpawnHeroes();

	Super::BeginPlay();
}


void AIKGameModeBase::SpawnHeroes()
{
	TArray<AActor*> marker;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnMarker::StaticClass(), marker);
	FRotator spawn_rotation = FRotator();
	if (marker.Num() > 0)
	{
		hero_spawn_position_ = marker[0]->GetActorLocation();
		spawn_rotation = marker[0]->GetActorRotation();
	}
	
	ULevelTransitionSubsystem* subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	auto save_data_array = subsystem->GetSpawnData();

	int32 counter = 0;
	for(const auto& hero_type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		if (save_data_array[hero_type].is_dead_ == false)
		{
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			param.bNoFail = true;
			AHeroBase* hero = GetWorld()->SpawnActor<AHeroBase>(hero_bp_class_[hero_type], hero_spawn_position_ + FVector(0, (300.f * (save_data_array.Num() - 1) / -2.f) + (counter * 300), 90), spawn_rotation, param);
			hero->SyncWithSpawnData(save_data_array[hero_type]);
			heroes_.Add(hero);
			counter += 1;
		}
		else
		{
			heroes_.Add(nullptr);
		}
	}
}

void AIKGameModeBase::SpawnEnemies()
{
	enemy_spawner_manager_ = NewObject<UEnemySpawnerManager>(this, enemy_spawner_manager_class_);
	enemy_spawner_manager_->Initialize(hero_spawn_position_);
	enemy_spawner_manager_->SpawnEnemies();
}

void AIKGameModeBase::ProceedGameFlowAfterUI()
{
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		if (has_game_won_)
		{	// Has game won
			hud->SwitchUIByState(ECombatEndState::ShowingEquipmentRewardUI);
		}
		else
		{	// game defeated.
			hud->SwitchUIByState(ECombatEndState::ShowingRunResultUI);
		}
	}
}

void AIKGameModeBase::SaveHeroSpawnData()
{
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	TMap<EHeroType, FSpawnData> spawn_map = level_transition_subsystem->GetSpawnData();
	for(EHeroType type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		int32 cur_idx = HeroTypeToInt(type);
		if (heroes_[cur_idx])
		{
			spawn_map[type].character_data_ = Cast<AHeroBase>(heroes_[cur_idx])->GetCharacterStat()->GetCharacterData();
		}
		else if(spawn_map[type].is_dead_ == false)
		{
			UGlobalBuffSubsystem* global_buff_subsystem = GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
			const EGlobalBuffType deathbound_type = HeroTypeToDeathbound(type);
			if (global_buff_subsystem->HasBuff(deathbound_type))
			{	// Consider the character is dead
				spawn_map[type].is_dead_ = true;
				global_buff_subsystem->RemoveBuff(deathbound_type);
			}
			else
			{	// When no debuff in the queue, apply debuff and revive it once.
				UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
				UDataTableManager* data_table_manager = instance->GetDataTableManager();
				
				spawn_map[type].character_data_ = data_table_manager->GetCharacterData(HeroTypeToCharacterType(type));
				global_buff_subsystem->AddBuff(deathbound_type);
			}
		}
	}
	
	level_transition_subsystem->UpdateSpawnData(spawn_map);
}

const TArray<TObjectPtr<AActor>>& AIKGameModeBase::GetHeroContainer() const noexcept
{
	return heroes_;
}

AActor* AIKGameModeBase::GetHero(EHeroType type) const noexcept
{
	return heroes_[HeroTypeToInt(type)];
}

const TArray<AActor*>& AIKGameModeBase::GetEnemyContainers() const noexcept
{
	return enemy_spawner_manager_->GetEnemies();
}

void AIKGameModeBase::RemoveHero(EHeroType hero_type)
{
	//1. 사망 작업 진행 ex)모션/사운드/사망 모션 진행 중 적이 공격하지 못하게 하기.
	//TODO

	//2. 사망 진행 작업이 끝나면 해당 index의 hero를 제거 후 null로 변경.
	heroes_[HeroTypeToInt(hero_type)] = nullptr;

	//3. Win-Lose Condition Check
	CheckWinLoseCondition();
}

void AIKGameModeBase::RemoveEnemy(AEnemyBase* enemy)
{
	if (enemy)
	{
		enemy_spawner_manager_->RemoveEnemy(enemy);
		CheckWinLoseCondition();
	}
}

void AIKGameModeBase::RemoveAllEnemy()
{
	enemy_spawner_manager_->RemoveAllEnemy();
	CheckWinLoseCondition();
}

void AIKGameModeBase::CheckWinLoseCondition()
{
	// Escape immediately if any side is not annihilated.
	if (!enemy_spawner_manager_->IsEnemyAllDefeated() && !IsDefeated())
	{
		return;
	}

	if (AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		pc->GetTargetingComponent()->StopTargeting();
	}


	// Function call matters. 
	// Need changes in CombatResultUI if the below line called after SaveHeroSpawnData.
	DisplayCombatResult();

	// Function call matters. 
	// Need changes in CombatResultUI if the below line called before DisplayCombatResult.
	SaveHeroSpawnData();


	if (enemy_spawner_manager_->IsEnemyAllDefeated())
	{
		OnGameWin();
	}
	else
	{
		OnGameLose();
	}
}

void AIKGameModeBase::OnGameWin()
{
	has_game_won_ = true;

	// Rewarded credits
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (instance)
	{
		UInventoryManager* inventory = instance->GetInventoryManager();
		UPerkModifierSubsystem* perk_modifier_subsystem = instance->GetSubsystem<UPerkModifierSubsystem>();
		if (inventory && perk_modifier_subsystem)
		{
			// @@ Improvements: Need to modify an amount of credits per combats.
			// i.e. -> ((current node level / 2) + 1) * 10;
			int32 credits = 50;
			credits *= perk_modifier_subsystem->GetCombatEndCreditsBonusPercentage();
			inventory->AddCredits(credits);
		}
	}

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::LevelWon);
}

void AIKGameModeBase::OnGameLose()
{
	if (IsAllHeroesPermanentlyDead())
	{
		has_game_won_ = false;

		UIKGameInstance* ik_instance = Cast<UIKGameInstance>(GetGameInstance());
		if (ik_instance)
		{
			ik_instance->ClearRunData();
		}
	}


	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::LevelDefeated);
}

void AIKGameModeBase::RecordDamage(float damage, TWeakObjectPtr<AActor> attacker)
{
	AHeroBase* hero = Cast<AHeroBase>(attacker);
	if (hero)
	{
		EHeroType type = hero->GetHeroType();

		if (gunner_damage_map_.Contains(type))
		{
			gunner_damage_map_[type] += damage;
		}
		else
		{
			gunner_damage_map_.Add(type, damage);
		}
	}
}

void AIKGameModeBase::SetGlobalTimeDilation(float time_dilation)
{
	if (time_dilation_manager_)
	{
		time_dilation_manager_->SetGlobalTimeDilation(GetWorld(), time_dilation);
	}
}

float AIKGameModeBase::GetGlobalTimeDilation() const
{
	if (time_dilation_manager_)
	{
		return time_dilation_manager_->GetGlobalTimeDilation(GetWorld());
	}
	return 0.f;
}

void AIKGameModeBase::SlowGlobalTimeDilation()
{
	if (time_dilation_manager_)
	{
		time_dilation_manager_->SlowGlobalTimeDilation(GetWorld());
	}
}

void AIKGameModeBase::RestoreGlobalTimeDilation()
{
	if (time_dilation_manager_)
	{
		time_dilation_manager_->RestoreGlobalTimeDilation(GetWorld());
	}
}

void AIKGameModeBase::SetDebugDrawActivated(bool activated)
{
	for (const auto& elem :heroes_)
	{
		if (elem)
		{
			Cast<AMeleeAIController>(Cast<APawn>(elem)->GetController())->SetDebugDrawActivated(activated);
		}
	}

	for (const auto& elem : enemy_spawner_manager_->GetEnemies())
	{
		if (elem)
		{
			Cast<AMeleeAIController>(Cast<APawn>(elem)->GetController())->SetDebugDrawActivated(activated);
		}
	}
}

void AIKGameModeBase::DisplayCombatResult()
{
	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();

	if (player_controller)
	{
		if (AIKHUD* hud = Cast<AIKHUD>(player_controller->GetHUD()))
		{
			hud->DisplayCombatResult(gunner_damage_map_);
		}
	}
}

bool AIKGameModeBase::IsDefeated() const
{
	for (AActor* elem : heroes_)
	{
		// hero become null explicitly if it died
		if (elem)
		{
			return false;
		}
	}
	return true;
}

bool AIKGameModeBase::IsAllHeroesPermanentlyDead() const
{
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	const auto& spawn_map = level_transition_subsystem->GetSpawnData();
	for(EHeroType type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		if (spawn_map[type].is_dead_ != true)
		{
			return false;
		}
	}
	return true;
}