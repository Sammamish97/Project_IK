/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.06.2025
Summary : Header file for an abstract class that has helper functions related to handle assets have rarity.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RarityAbstractObject.generated.h"

enum class ERarity : uint8;
class UDataTable;


USTRUCT(BlueprintType)
struct FRarityData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Item")
	ERarity rarity_;
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API URarityAbstractObject : public UObject
{
	GENERATED_BODY()
	
protected:
	ERarity GetRarityRandomly(ERarity weight_rarity) const;
	// Return data contains how many rarity produced.
	TMap<ERarity, int32> GetRaritiesRandomly(ERarity weight_rarity, int32 n) const;
	void CategorizeByRarity(UDataTable* data_table);
	FRarityData* GetRandomDataByRarity(ERarity rarity) const;
	TArray<FRarityData*> GetUniqueRandomData(TMap<ERarity, int32> rarity_count) const;

private:
	TArray<TPair<ERarity, int32>> GetRarityWeights(ERarity weight_rarity) const;

protected:


	TArray<FRarityData*> rarity_B, rarity_A, rarity_S;
};
