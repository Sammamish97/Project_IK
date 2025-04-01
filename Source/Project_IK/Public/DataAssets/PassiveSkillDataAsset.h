/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Header file for Passive Skill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/PassiveSkillData.h"
#include "PassiveSkillDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UPassiveSkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FPassiveSkillData GetPassiveKillData(EPassiveSkillType type);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive Skill Data", meta = (AllowPrivateAccess = "true"))
	TMap<EPassiveSkillType, FPassiveSkillData> passive_skill_data_map_;
};
