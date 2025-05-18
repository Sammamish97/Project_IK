/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.17.2025
Summary : Header file for the unit type data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "Managers/EnumCluster.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UnitTypeDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UUnitTypeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	TSubclassOf<class AUnit> GetUnitClass(ECharacterType unit_type);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Type Data", meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterType, TSubclassOf<class AUnit>> unit_type_map_;
};
