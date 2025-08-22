/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Header file for Active Skill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/ActiveSkillData.h"
#include "ActiveSkillDataAsset.generated.h"
UCLASS()
class PROJECT_IK_API UActiveSkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FActiveSkillData GetActiveSkillData(EActiveSkillType type);
	FActiveSkillData GetActiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common);
	FActiveSkillData GetActiveSkillDataByRarity(ERarity rarity = ERarity::Common);
	TArray<FActiveSkillData> GetUniqueActiveSkillDataRandomly(int32 n, ERarity weight_rarity = ERarity::Common);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Skill Data", meta = (AllowPrivateAccess = "true"))
	TMap<EActiveSkillType, FActiveSkillData> active_skill_data_map_;
};
