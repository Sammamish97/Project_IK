/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for game mode.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Managers/EnumCluster.h"

#include "IKGameModeBase.generated.h"

class UTimeDilationManager;
class UEnemySpawnerManager;

UCLASS()
class PROJECT_IK_API AIKGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AIKGameModeBase();

	virtual void BeginPlay() override;

	void SpawnHeroes();
	void SpawnEnemies();

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetHeroContainer() const noexcept;

	UFUNCTION(BlueprintPure)
	AActor* GetHero(EHeroType type) const noexcept;

	void ProceedGameFlowAfterUI();

	UFUNCTION(BlueprintPure)
	const TArray<AActor*>& GetEnemyContainers() const noexcept;
	UFUNCTION(BlueprintCallable)
	void RemoveHero(EHeroType hero_type);
	UFUNCTION(BlueprintCallable)
	void RemoveEnemy(AEnemyBase* enemy);
	UFUNCTION(BlueprintCallable)
	void RemoveAllEnemy();

	UFUNCTION()
	void RecordDamage(float damage, TWeakObjectPtr<AActor> attacker);

	UFUNCTION(BlueprintCallable)
	void SetGlobalTimeDilation(float time_dilation);
	UFUNCTION(BlueprintCallable)
	float GetGlobalTimeDilation() const;
	UFUNCTION(BlueprintCallable)
	void SlowGlobalTimeDilation();
	UFUNCTION(BlueprintCallable)
	void RestoreGlobalTimeDilation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<UEnemySpawnerManager> enemy_spawner_manager_class_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	TArray<TSubclassOf<class AHeroBase>> hero_bp_class_;
	
protected:

	void SaveHeroSpawnData();
	void CheckWinLoseCondition();

	void OnGameWin();

	void OnGameLose();

	void DisplayCombatResult();
	bool IsDefeated() const;

	FVector hero_spawn_position_;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> heroes_;

	UPROPERTY()
	TMap<EHeroType, float> gunner_damage_map_;

	UPROPERTY()
	TObjectPtr<UTimeDilationManager> time_dilation_manager_;

	UPROPERTY()
	TObjectPtr<UEnemySpawnerManager> enemy_spawner_manager_;

	bool has_game_won_ = false;
};
