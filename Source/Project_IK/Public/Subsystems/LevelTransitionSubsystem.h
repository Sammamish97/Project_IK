/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Header file for managing trasition between levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/SupportSkillData.h"
#include "Structs/SpawnData.h"
#include "LevelTransitionSubsystem.generated.h"

UCLASS()
class PROJECT_IK_API ULevelTransitionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateSpawnData(const TMap<EHeroType, FSpawnData>& data);
	UFUNCTION(BlueprintCallable)
	void UpdateSpawnDataIdx(EHeroType type, FSpawnData data);

	UFUNCTION(BlueprintCallable)
	void UpdateSupportSkillDataIdx(int32 idx, FSupportSkillData data);
	UFUNCTION(BlueprintCallable)
	void UpdateSupportSkillData(const TMap<int32, FSupportSkillData>& data);
	
	UFUNCTION(BlueprintCallable)
	void OpenMapLevel(UWorld* world);
	
	UFUNCTION(BlueprintCallable)
	void OpenLevel(UWorld* world, FIntPoint map_position);
	
	UFUNCTION(BlueprintCallable)
	const TMap<EHeroType, FSpawnData>& GetSpawnData() const;

	FSpawnData GetSpawnData(EHeroType type) const;

	UFUNCTION(BlueprintCallable)
	const TMap<int32, FSupportSkillData>& GetSupportSkillData() const;

protected:
	UPROPERTY()
	TMap<EHeroType, FSpawnData> spawn_data_;
	
	UPROPERTY()
	TMap<int32, FSupportSkillData> support_skill_data_;
};
