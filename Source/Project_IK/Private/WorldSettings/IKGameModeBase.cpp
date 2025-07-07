/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKGameModeBase.h"
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
#include "UI/IKMaps.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Managers/DataTableManager.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
}

void AIKGameModeBase::StartPlay()
{
	Super::StartPlay();
	for (auto& elem : heroes_)
	{
		auto hero_ptr = elem.Value;
		Cast<AHeroBase>(hero_ptr)->GetPassiveSkillMechanics()->InitPassiveSkill();
		GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->ApplyBuff(hero_ptr);
	}
}

void AIKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	hero_spawn_position_ = FVector();
	time_dilation_manager_ = NewObject<UTimeDilationManager>(this);
	SpawnHeroes();

	// SpawnEnemies function should be called after SpawnHeroes has been called.
	SpawnEnemies();
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
			AHeroBase* hero = GetWorld()->SpawnActor<AHeroBase>(hero_bp_class_[hero_type], hero_spawn_position_ + FVector(0, (300.f * (save_data_array.Num() - 1) / -2.f) + (counter * 300), 90), spawn_rotation);
			hero->SyncWithSpawnData(save_data_array[hero_type]);
			heroes_.Add({hero_type, hero});
			counter += 1;
		}
	}
}

void AIKGameModeBase::SpawnEnemies()
{
	enemy_spawner_manager_ = NewObject<UEnemySpawnerManager>(this, enemy_spawner_manager_class_);

	FIntPoint player_position = Cast<UIKGameInstance>(GetGameInstance())->GetMapPtr()->GetPlayerGridPosition();
	// Decide the number of enemy waves using player's current progress.
	if (player_position.X < 3)
	{
		// Hero spawn position initialized after SpawnHeroes has been called.
		enemy_spawner_manager_->Initialize(hero_spawn_position_, 2);
	}
	else
	{
		enemy_spawner_manager_->Initialize(hero_spawn_position_, 4);
	}
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
			hud->SwitchUIByState(ECombatEndState::ShowingToMainmenu);
		}
	}
}

void AIKGameModeBase::SaveHeroSpawnData()
{
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	TArray<FSpawnData> spawn_data = level_transition_subsystem->GetSpawnData();
	for (int32 i = 0; i < heroes_.Num(); ++i)
	{
		if (heroes_[i] != nullptr)
		{
			spawn_map[hero_type].is_dead_ = true;
			spawn_data[i].character_data_ = Cast<AHeroBase>(heroes_[i])->GetCharacterStat()->GetCharacterData();
		}
		else if(spawn_data[i].is_dead_ == false)
		{
			EHeroType hero_type = IntToHeroType(i);
			UGlobalBuffSubsystem* global_buff_subsystem = GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
			const EGlobalBuffType deathbound_type = HeroTypeToDeathbound(hero_type);
			if (global_buff_subsystem->HasBuff(deathbound_type))
			{	// Consider the character is dead
				spawn_data[i].is_dead_ = true;
				global_buff_subsystem->RemoveBuff(deathbound_type);
			}
			else
			{	// When no debuff in the queue, apply debuff and revive it once.
				UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
				UDataTableManager* data_table_manager = instance->GetDataTableManager();
				
				spawn_data[i].character_data_ = data_table_manager->GetCharacterData(HeroTypeToCharacterType(hero_type));
				global_buff_subsystem->AddBuff(deathbound_type);
			}
		}
	}
	level_transition_subsystem->UpdateSpawnData(spawn_data);
}

TMap<EHeroType, TObjectPtr<AActor>> AIKGameModeBase::GetHeroContainer() const noexcept
{
	return heroes_;
}

int32 AIKGameModeBase::GetHeroCount() const noexcept
{
	int32 count = 0;
	for (const auto& elem : heroes_)
	{
		TWeakObjectPtr<AActor> hero_ptr = elem.Value;
		if (hero_ptr.IsValid())
		{
			++count;
		}
	}
	return count;
}

AActor* AIKGameModeBase::GetHero(EHeroType type) const noexcept
{
	if(heroes_.Contains(type))
	{
		return heroes_[type];
	}
	return nullptr;
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
	heroes_.Remove(hero_type);

	//3. SpawnData의 dead를 false로 update.
	ULevelTransitionSubsystem* level_transition_cache = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	FSpawnData spawn_data = level_transition_cache->GetSpawnData(hero_type);
	spawn_data.is_dead_ = true;
	level_transition_cache->UpdateSpawnDataIdx(hero_type, spawn_data);

	//4. Win-Lose Condition Check
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
}

void AIKGameModeBase::OnGameLose()
{
	if (IsAllHeroesPermanentlyDead())
	{
		has_game_won_ = false;
	}

	DisplayCombatResult();
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

void AIKGameModeBase::DisplayCombatResult()
{
	APlayerController* player_controller = GetWorld()->GetFirstPlayerController();

	if (player_controller)
	{
		if (AIKHUD* hud = Cast<AIKHUD>(player_controller->GetHUD());)
		{
			hud->DisplayCombatResult(gunner_damage_map_);
		}
	}
}

bool AIKGameModeBase::IsDefeated() const
{
	for (const auto& elem : heroes_)
	{
		TWeakObjectPtr<AActor> actor = elem.Value;
		// hero become null explicitly if it died
		if (!actor.IsExplicitlyNull())
		{
			return false;
		}
	}
	return true;
}

bool AIKGameModeBase::IsAllHeroesPermanentlyDead() const
{
	ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	TArray<FSpawnData> spawn_data = level_transition_subsystem->GetSpawnData();

	for (int32 i = 0; i < heroes_.Num(); ++i)
	{
		if (spawn_data[i].is_dead_ != true)
		{
			return false;
		}
	}
	return true;
}