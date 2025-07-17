/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.15.2025
Summary : Header file for a subsystem that manages data about Gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Managers/EnumCluster.h"
#include "GotchaSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGotchaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetNumMaxPull(int32 num_max_pull);
	UFUNCTION(BlueprintPure)
	int32 GetNumMaxPull() const;

	UFUNCTION(BlueprintCallable)
	void SetSeedWeightRarity(ERarity seed_weight_rarity);
	UFUNCTION(BlueprintPure)
	ERarity GetSeedWeightRarity() const;

protected:
	int32 num_max_pull_ = 0;
	ERarity seed_weight_rarity_ = ERarity::Common;
};
