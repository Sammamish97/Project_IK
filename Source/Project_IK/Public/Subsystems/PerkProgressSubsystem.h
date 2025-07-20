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
#include "Managers/EnumCluster.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PerkProgressSubsystem.generated.h"

enum class EHeroType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkProgressSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:

	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	virtual void Deinitialize() override;

	const TSet<int32>& GetProgress() const;
	// Return false when there is a recorded progress already.
	bool AddProgress(int32 progress);

protected:
	TSet<int32> progress_;	
};
