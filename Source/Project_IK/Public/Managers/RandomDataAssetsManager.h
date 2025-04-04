/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for a provider data assets randomly.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomDataAssetsManager.generated.h"

struct FItemData;
enum class ERarity : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API URandomDataAssetsManager : public UObject
{
	GENERATED_BODY()
public:
	template<typename TMapKey, typename TMapValue>
	static TMapValue GetDataAssetRandomly(ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map);
	//TArray<FItemData> GetUniqueItemDataRandomly(int32 n, ERarity rarity) const;

protected:
	static ERarity GetRarityRandomly(ERarity weight_rarity);
	static TMap<ERarity, int32> GetRaritiesRandomly(ERarity weight_rarity, int32 n);
	static void CategorizeByRarity();
	static TArray<TPair<ERarity, int32>> GetRarityWeights(ERarity weight_rarity);

};

template<typename TMapKey, typename TMapValue>
inline TMapValue URandomDataAssetsManager::GetDataAssetRandomly(ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map)
{
	ERarity rarity = GetRarityRandomly(weight_rarity);

	TArray<TMapKey> asset_candidates;

	for (const auto& element : map)
	{
		if (element.Value.rarity_ == rarity)
		{
			asset_candidates.Add(element.Key);
		}
	}

	int32 rand_index = FMath::RandRange(0, asset_candidates.Num() - 1);
	return map[asset_candidates[rand_index]];
}
