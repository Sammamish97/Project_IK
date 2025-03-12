/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.11.2025
Summary : Header file for data assets for global buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/GlobalBuff.h"
#include "GlobalBuffDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGlobalBuffDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EGlobalBuffType, FGlobalBuffData> global_buff_data_assets_;
};
