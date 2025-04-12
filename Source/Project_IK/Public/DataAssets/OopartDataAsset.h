/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Header file for Oopart Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/OopartData.h"
#include "OopartDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UOopartDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FOopartData GetOopartData(EOopartType type);
	FOopartData GetOopartDataRandomly(ERarity weight_rarity = ERarity::Common);
	TArray<FOopartData> GetUniqueOopartDataRandomly(int32 n, ERarity weight_rarity = ERarity::Common);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Oopart Data", meta = (AllowPrivateAccess = "true"))
	TMap<EOopartType, FOopartData> oopart_data_map_;
};
