/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.11.2025
Summary : Header file for a subsystem that manages global buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GlobalBuffSubsystem.generated.h"

struct FGlobalBuffData;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGlobalBuffSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddBuff(const FGlobalBuffData& buff);

	void ApplyBuff(UObject* object_applied);

	void UpdateBuffDurations();

protected:
	TArray<FGlobalBuffData> buffs_;
};
