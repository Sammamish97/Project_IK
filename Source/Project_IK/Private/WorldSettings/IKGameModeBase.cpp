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
#include "Components/TargetingComponent.h"
#include "Managers/TimeDilationManager.h"

#include "WorldSettings/IKHUD.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Environments/SpawnMarker.h"
#include "Structs/SpawnData.h"
#include "Subsystems/LevelTransitionSubsystem.h"

AIKGameModeBase::AIKGameModeBase()
	: Super::AGameModeBase()
{
}

void AIKGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	time_dilation_manager = NewObject<UTimeDilationManager>(this);
	SpawnHeroes();
}


void AIKGameModeBase::SpawnHeroes()
{
	TArray<AActor*> marker;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnMarker::StaticClass(), marker);
	FVector spawn_position = FVector();
	FRotator spawn_rotation = FRotator();
	if (marker.Num() > 0)
	{
		spawn_position = marker[0]->GetActorLocation();
		spawn_rotation = marker[0]->GetActorRotation();
	}

	ULevelTransitionSubsystem* subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	auto save_data_array = subsystem->GetSpawnData();
	
	for (int32 i = 0; i < save_data_array.Num(); ++i)
	{
		AHeroBase* hero = GetWorld()->SpawnActor<AHeroBase>(save_data_array[i].character_data_.unit_class_, spawn_position + FVector(0, (300.f * (save_data_array.Num() - 1) / -2.f ) + (i * 300), 90), spawn_rotation);
		hero->SpawnDefaultController();
		hero->GetComponentByClass<UCharacterStatComponent>()->SetCharacterData(save_data_array[0].character_data_);
		hero->Initialize();
		heroes_.Add(hero);
	}
}

void AIKGameModeBase::SaveHeroSpawnData()
{
	TArray<FSpawnData> spawn_data;
	for(auto hero : heroes_)
	{
		FSpawnData cur_data;
		cur_data.character_data_ = Cast<AHeroBase>(hero)->GetCharacterStat()->GetCharacterData();
		spawn_data.Add(cur_data);
	}
	GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->UpdateSpawnData(spawn_data);
}

TArray<AActor*> AIKGameModeBase::GetHeroContainers() const noexcept
{
	return heroes_;
}

TArray<AActor*> AIKGameModeBase::GetEnemyContainers() const noexcept
{
	return enemies_;
}

void AIKGameModeBase::RemoveHero(AActor* hero)
{
	if (hero)
	{
		heroes_.Remove(hero);
		CheckWinLoseCondition();
	}
}

void AIKGameModeBase::RemoveEnemy(AActor* enemy)
{
	if (enemy)
	{
		enemies_.Remove(enemy);
		CheckWinLoseCondition();
	}
}

void AIKGameModeBase::CheckWinLoseCondition()
{
	// Escape immediately if any side is not annihilated.
	if (enemies_.Num() > 0 && heroes_.Num() > 0)
	{
		return;
	}

	DisplayCombatResult();
	if(	AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		pc->GetTargetingComponent()->StopTargeting();
	}

	if (enemies_.Num() <= 0)
	{
		OnGameWin();
		SaveHeroSpawnData();
	}
	else if (heroes_.Num() <= 0)
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
	if (time_dilation_manager)
	{
		time_dilation_manager->SetGlobalTimeDilation(GetWorld(), time_dilation);
	}
}

inline float AIKGameModeBase::GetGlobalTimeDilation() const
{
	if (time_dilation_manager)
	{
		return time_dilation_manager->GetGlobalTimeDilation(GetWorld());
	}
	return 0.f;
}

void AIKGameModeBase::SlowGlobalTimeDilation()
{
	if (time_dilation_manager)
	{
		time_dilation_manager->SlowGlobalTimeDilation(GetWorld());
	}
}

void AIKGameModeBase::RestoreGlobalTimeDilation()
{
	if (time_dilation_manager)
	{
		time_dilation_manager->RestoreGlobalTimeDilation(GetWorld());
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
			hud->DisplayCombatResult(heroes_, gunner_damage_map_);
		}
	}
}