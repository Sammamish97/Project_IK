/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the Support SKill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/SupportSkillData.h"
#include "SupportSkillDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API USupportSkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FSupportSkillData GetSupportSkillClass(ESupportSkillType type);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Active Skill Data", meta = (AllowPrivateAccess = "true"))
	TMap<ESupportSkillType, FSupportSkillData> support_skill_data_map_;
};
