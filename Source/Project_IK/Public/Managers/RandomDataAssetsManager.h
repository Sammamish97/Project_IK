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
#include "Subsystems/RandomNumberGeneratorSubsystem.h"
#include "RandomDataAssetsManager.generated.h"

enum class EItemType : uint8;
enum class ERarity : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API URandomDataAssetsManager : public UObject
{
	GENERATED_BODY()
public:
	static constexpr int32 TOTAL_WEIGHT = 100;

	template<typename TMapKey, typename TMapValue>
	static TMapValue GetDataAssetRandomly(ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world);
	template<typename TMapKey, typename TMapValue>
	static TArray<TMapValue> GetDataAssetRandomly(int32 n, ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world);
	template<typename TMapKey, typename TMapValue>
	static TArray<TMapValue> GetUniqueDataAssetsRandomly(int32 n, ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world);
	template<typename TMapKey, typename TMapValue>
	static TMapValue GetDataAssetByRarity(ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world);
	template<typename TMapKey, typename TMapValue>
	static TArray<TMapValue> GetDataAssetByRarity(int32 n, ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world);

protected:
	static ERarity GetRarityRandomly(ERarity weight_rarity, UWorld* world);
	template<typename TMapKey, typename TMapValue>
	static TMap<ERarity, int32> GetRaritiesRandomly(ERarity weight_rarity, int32 n, const TMap<TMapKey, TMapValue>& map, const TMap<ERarity, TArray<TMapKey>>& keys_classified_by_rarity, UWorld* world);
	static TArray<TPair<ERarity, int32>> GetRarityWeights(ERarity weight_rarity);

};

template<typename TMapKey, typename TMapValue>
inline TMapValue URandomDataAssetsManager::GetDataAssetRandomly(ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world)
{
	return GetDataAssetRandomly(1, weight_rarity, map, world)[0];
}

template<typename TMapKey, typename TMapValue>
inline TArray<TMapValue> URandomDataAssetsManager::GetDataAssetRandomly(int32 n, ERarity weight_rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world)
{
	ERarity rarity = GetRarityRandomly(weight_rarity, world);

	TArray<TMapKey> asset_candidates;

	for (const auto& element : map)
	{
		if (element.Value.rarity_ == rarity)
		{
			asset_candidates.Add(element.Key);
		}
	}

	TArray<TMapValue> results;
	//checkf(!asset_candidates.IsEmpty(), TEXT("No elements that matches weight_rarity!"));
	if (asset_candidates.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No elements that matches weight_rarity!"));
		return GetDataAssetRandomly(n, ERarity::Common, map, world);
	}
	for (int32 i = 0; i < n; i++)
	{
		int32 rand_index = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, asset_candidates.Num() - 1);
		results.Add(map[asset_candidates[rand_index]]);
	}

	return results;
}

template<typename TMapKey, typename TMapValue>
inline TArray<TMapValue> URandomDataAssetsManager::GetUniqueDataAssetsRandomly(int32 n, ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world)
{

	TArray<TMapValue> return_array;

	if (n <= 0)
	{
		return return_array;
	}

	if (n <= 1)
	{
		return_array.Add(GetDataAssetRandomly(rarity, map, world));
		return return_array;
	}

	TMap<ERarity, TArray<TMapKey>> keys_classified_by_rarity;
	keys_classified_by_rarity.FindOrAdd(ERarity::Common);
	keys_classified_by_rarity.FindOrAdd(ERarity::Rare);
	keys_classified_by_rarity.FindOrAdd(ERarity::Legendary);
	for (const auto& [Key, Value] : map)
	{
		keys_classified_by_rarity[Value.rarity_].Add(Key);
	}

	TMap<ERarity, int32> rarities = GetRaritiesRandomly(rarity, n, map, keys_classified_by_rarity, world);


	const TArray<TMapKey>* rarity_array = nullptr;

	for (const TPair<ERarity, int32>& count_pair : rarities)
	{
		if (count_pair.Value <= 0)
		{
			continue;
		}

		rarity_array = &keys_classified_by_rarity[count_pair.Key];


		TArray<int32> indices;
		for (int32 i = 0; i < rarity_array->Num(); i++)
		{
			indices.Add(i);
		}

		// Shuffle index

		for (int32 i = indices.Num() - 1; i > 0; --i)
		{
			int32 shuffle_index = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, i);
			if (i == shuffle_index)
			{
				continue;
			}
			indices.Swap(i, shuffle_index);
		}

		for (int32 i = 0; i < count_pair.Value; i++)
		{
			return_array.Add(map[(*rarity_array)[indices[i]]]);
		}
	}

	return return_array;
}

template<typename TMapKey, typename TMapValue>
inline TMapValue URandomDataAssetsManager::GetDataAssetByRarity(ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world)
{
	return GetDataAssetByRarity(1, rarity, map, world)[0];
}

template<typename TMapKey, typename TMapValue>
inline TArray<TMapValue> URandomDataAssetsManager::GetDataAssetByRarity(int32 n, ERarity rarity, const TMap<TMapKey, TMapValue>& map, UWorld* world)
{
	TArray<TMapKey> asset_candidates;

	for (const auto& element : map)
	{
		if (element.Value.rarity_ == rarity)
		{
			asset_candidates.Add(element.Key);
		}
	}

	TArray<TMapValue> results;
	//checkf(!asset_candidates.IsEmpty(), TEXT("No elements that matches weight_rarity!"));
	if (asset_candidates.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No elements that matches weight_rarity!"));
		return GetDataAssetByRarity(n, ERarity::Common, map, world);
	}
	for (int32 i = 0; i < n; i++)
	{
		int32 rand_index = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, asset_candidates.Num() - 1);
		results.Add(map[asset_candidates[rand_index]]);
	}

	return results;
}

template<typename TMapKey, typename TMapValue>
inline TMap<ERarity, int32> URandomDataAssetsManager::GetRaritiesRandomly(ERarity weight_rarity, int32 n, const TMap<TMapKey, TMapValue>& map, const TMap<ERarity, TArray<TMapKey>>& keys_classified_by_rarity, UWorld* world)
{
	TArray<TPair<ERarity, int32>> weights = GetRarityWeights(weight_rarity);


	TMap<ERarity, int32> rarity_count = {
		TPair<ERarity, int32>(ERarity::Common, 0),
		TPair<ERarity, int32>(ERarity::Rare, 0),
		TPair<ERarity, int32>(ERarity::Legendary, 0)
	};

	int32 rarities_size = FMath::Min(n, map.Num());

	int32 i = 0;
	while (i < rarities_size)
	{
		const int32 random_value = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, TOTAL_WEIGHT);

		// Count up rarity based on the random value
		int32 cumulative_weight = 0;
		for (const auto& pair : weights)
		{
			cumulative_weight += pair.Value;
			if (random_value <= cumulative_weight)
			{
				int32 data_size = keys_classified_by_rarity[pair.Key].Num();

				// In order to return unique data, increase only when the data size is proper.
				if (rarity_count[pair.Key] < data_size)
				{
					rarity_count[pair.Key] += 1;
					++i;
				}
				break;
			}
		}
	}

	return rarity_count;
}
