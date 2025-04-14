/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.14.2025
Summary : Header file for data assets for CC information.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/CrowdControlInfoData.h"
#include "CrowdControlInfoDataAsset.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCrowdControlInfoDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UTexture2D* GetCCTexture(ECCType cc_type);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECCType, FCrowdControlInfoData> cc_info_data_map_;
};
