/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Header file for the rune data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/RuneData.h"
#include "RuneDataAsset.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API URuneDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FRuneData GetRuneSetData(ERuneSetType type);
	FRuneData GetRuneSetDataRandomly(UWorld* world, ERarity weight_rarity = ERarity::Common);
	TArray<FRuneData> GetRuneSetDataRandomly(int32 n, UWorld* world, ERarity weight_rarity = ERarity::Common);
	TArray<FRuneData> GetUniqueRuneSetDataRandomly(int32 n, UWorld* world, ERarity weight_rarity = ERarity::Common);
	
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TMap<ERuneSetType, FRuneData> rune_data_map_;
};
