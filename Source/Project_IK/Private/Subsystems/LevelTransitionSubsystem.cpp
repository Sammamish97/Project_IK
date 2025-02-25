/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Source file for managing trasition between levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Environments/SpawnMarker.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Managers/EnumCluster.h"
#include "Structs/SpawnData.h"
#include "UI/IKMaps.h"
#include "WorldSettings/IKGameModeBase.h"

class UIKGameInstance;

void ULevelTransitionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void ULevelTransitionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelTransitionSubsystem::InitHeroData(const TArray<EHeroType>& hero_types)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	for(const auto& type : hero_types)
	{
		FSpawnData spawn_data;
		if (UDataTableManager* data_table = instance->GetDataTableManager())
		{
			spawn_data.character_data_ = *(data_table->GetCharacterData(type));
		}
		spawn_data_.Add(spawn_data);
	}
}

void ULevelTransitionSubsystem::SaveData(UWorld* world)
{
	AGameModeBase* raw_game_mode = UGameplayStatics::GetGameMode(world);
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(raw_game_mode);
	if (game_mode)
	{
		TArray<AActor*> heroes = game_mode->GetHeroContainers();
		for (int32 i = 0; i < heroes.Num(); i++)
		{
			AHeroBase* hero = Cast<AHeroBase>(heroes[i]);
			const UCharacterStatComponent* stat_component = hero->GetCharacterStat();

			// @@ TODO: Need to save proper data.
			spawn_data_[i].character_data_ = stat_component->GetCharacterData();
		}
	}
}

void ULevelTransitionSubsystem::OpenLevel(UWorld* world, FIntPoint map_position)
{
	SaveData(world);

	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	FMapNode node = instance->GetMapPtr()->GetNode(map_position.X, map_position.Y);
	switch (node.type)
	{
	case NodeType::None:
		UE_LOG(LogTemp, Warning, TEXT("ULevelTransitionManager::OpenLevel -> Tried to go to invalid map node"));
		break;
	case NodeType::Enemy:
		UGameplayStatics::OpenLevel(world, FName("CombatLevel"));
		instance->GetMapPtr()->SetPlayerGridPosition(map_position);
		break;
	default:
		break;
	}
}

void ULevelTransitionSubsystem::PrepareLevel(UWorld* world)
{
	SpawnHeroes(world);
}

const TArray<FSpawnData>& ULevelTransitionSubsystem::GetSavedData() const
{
	return spawn_data_;
}

FSpawnData ULevelTransitionSubsystem::GetSavedData(int idx) const
{
	return spawn_data_[idx];
}

void ULevelTransitionSubsystem::SpawnHeroes(UWorld* world)
{
	TArray<AActor*> marker;
	UGameplayStatics::GetAllActorsOfClass(world, ASpawnMarker::StaticClass(), marker);
	FVector spawn_position = FVector();
	FRotator spawn_rotation = FRotator();
	if (marker.Num() > 0)
	{
		spawn_position = marker[0]->GetActorLocation();
		spawn_rotation = marker[0]->GetActorRotation();
	}

	for (int32 i = 0; i < spawn_data_.Num(); ++i)
	{
		AHeroBase* hero = world->SpawnActor<AHeroBase>(spawn_data_[i].character_data_.unit_class_, spawn_position + FVector(0, (300.f * (spawn_data_.Num() - 1) / -2.f ) + (i * 300), 90), spawn_rotation);
		hero->SpawnDefaultController();
		hero->GetComponentByClass<UCharacterStatComponent>()->SetCharacterData(spawn_data_[0].character_data_);
		hero->Initialize();
	}
}

// void ULevelTransitionSubsystem::SpawnEnemies(UWorld* world)
// {
// 	for (int32 i = 0; i < 2; i++)
// 	{
// 		AEnemyBase* enemy = world->SpawnActor<AEnemyBase>(enemy_blueprint_, FVector(600, 0 + (200.f * i), 90), FRotator(0, 180, 0));
// 		enemy->SpawnDefaultController();
// 	}
// }