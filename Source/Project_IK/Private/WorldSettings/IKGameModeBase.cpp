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

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
}

void AIKGameModeBase::StartPlay()
{
	Super::StartPlay();
	for (auto& elem : heroes_)
	{
		Cast<AHeroBase>(elem)->GetPassiveSkillMechanics()->InitPassiveSkill();
		GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->ApplyBuff(elem);
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

	for (int32 i = 0; i < save_data_array.Num(); ++i)
	{
		if (save_data_array[i].is_dead_)
		{
			heroes_.Add(nullptr);
			continue;
		}
		AHeroBase* hero = GetWorld()->SpawnActor<AHeroBase>(hero_bp_class_[i], hero_spawn_position_ + FVector(0, (300.f * (save_data_array.Num() - 1) / -2.f) + (i * 300), 90), spawn_rotation);
		hero->EquipGears(save_data_array[i]);
		heroes_.Add(hero);
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

void AIKGameModeBase::SaveHeroSpawnData()
{
	TArray<FSpawnData> spawn_data;
	for (auto hero : heroes_)
	{
		FSpawnData cur_data;
		if (hero != nullptr)
		{
			cur_data.character_data_ = Cast<AHeroBase>(hero)->GetCharacterStat()->GetCharacterData();
			spawn_data.Add(cur_data);
		}
		else
		{
			cur_data.is_dead_ = true;
			spawn_data.Add(cur_data);
		}

	}
	GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->UpdateSpawnData(spawn_data);
}

TArray<AActor*> AIKGameModeBase::GetHeroContainer() const noexcept
{
	return heroes_;
}

int32 AIKGameModeBase::GetHeroCount() const noexcept
{
	int32 count = 0;
	for (TWeakObjectPtr<AActor> hero : heroes_)
	{
		if (hero.IsValid())
		{
			++count;
		}
	}
	return count;
}

AActor* AIKGameModeBase::GetHero(EHeroType type) const noexcept
{
	if (heroes_.IsValidIndex(HeroTypeToInt(type)))
	{
		return heroes_[HeroTypeToInt(type)];
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
	int32 target_idx = HeroTypeToInt(hero_type);
	if (heroes_.IsValidIndex(target_idx))
	{
		heroes_[target_idx] = nullptr;
		//3. SpawnData의 dead를 false로 update.
		ULevelTransitionSubsystem* level_transition_cache = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
		FSpawnData spawn_data = level_transition_cache->GetSpawnData(target_idx);
		spawn_data.is_dead_ = true;
		level_transition_cache->UpdateSpawnDataIdx(target_idx, spawn_data);

		//4. Win-Lose Condition Check
		CheckWinLoseCondition();
	}
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

	DisplayCombatResult();
	if (AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		pc->GetTargetingComponent()->StopTargeting();
	}

	if (enemy_spawner_manager_->IsEnemyAllDefeated())
	{
		OnGameWin();
		SaveHeroSpawnData();
	}
	else
	{
		OnGameLose();
	}
}

void AIKGameModeBase::RecordDamage(float damage, TWeakObjectPtr<AActor> attacker)
{
	if (Cast<AHeroBase>(attacker))
	{
		if (gunner_damage_map_.Contains(attacker))
		{
			gunner_damage_map_[attacker] += damage;
		}
		else
		{
			gunner_damage_map_.Add(attacker, damage);
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
		AIKHUD* hud = Cast<AIKHUD>(player_controller->GetHUD());
		if (hud)
		{
			TArray<AActor*> alive_heroes;
			for (TWeakObjectPtr<AActor> actor : heroes_)
			{
				if (actor.IsValid())
				{
					alive_heroes.Add(actor.Get());
				}
			}

			hud->DisplayCombatResult(alive_heroes, gunner_damage_map_);
		}
	}
}

bool AIKGameModeBase::IsDefeated() const
{
	for (TWeakObjectPtr<AActor> hero : heroes_)
	{
		// hero become null explicitly if it died
		if (!hero.IsExplicitlyNull())
		{
			return false;
		}
	}
	return true;
}
