/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.8.2025
Summary : Header file for a subsystem that manages perk progresses.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Structs/PerkNodeDetail.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PerkProgressSubsystem.generated.h"

enum class EHeroType : uint8;

UCLASS()
class PROJECT_IK_API UPerkProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	void SavePerkDetails(EPerkNodeType type, FPerkNodeDetail detail);
	FPerkNodeDetail LoadPerkDetails(EPerkNodeType key);
	bool HasSavedPerkDetails(EPerkNodeType key);
	TMap<EPerkNodeType, FPerkNodeDetail> LoadAllPerkDetails();

	void SavePerkPoint(int32 perk_point);
	int32 LoadPerkPoint();
	
	void SavePerkDataToDisk();

	void Clear();

	void ApplyPerkEffectsInMap();
	void RemoveAllPerkEffects();

protected:
	UPROPERTY()
	int32 perk_points_;
	
	UPROPERTY()
	TMap<EPerkNodeType, FPerkNodeDetail> perk_node_map_;	
};
