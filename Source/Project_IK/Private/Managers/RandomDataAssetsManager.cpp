/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for a provider data assets randomly.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RandomDataAssetsManager.h"

#include "Structs/ItemData.h"
#include "Managers/EnumCluster.h"

ERarity URandomDataAssetsManager::GetRarityRandomly(ERarity weight_rarity)
{
	TArray<TPair<ERarity, int32>> weights = GetRarityWeights(weight_rarity);

	constexpr int32 total_weight = 100;
	int32 random_value = FMath::RandRange(0, total_weight);

	// Return rarity based on the random value
	int32 cumulative_weight = 0;
	for (const auto& pair : weights)
	{
		cumulative_weight += pair.Value;
		if (random_value <= cumulative_weight)
		{
			return pair.Key;
		}
	}
	return ERarity::Common;
}

TMap<ERarity, int32> URandomDataAssetsManager::GetRaritiesRandomly(ERarity weight_rarity, int32 n)
{
	//TArray<TPair<ERarity, int32>> weights = GetRarityWeights(weight_rarity);


	//TMap<ERarity, int32> rarity_count = {
	//	TPair<ERarity, int32>(ERarity::Common, 0),
	//	TPair<ERarity, int32>(ERarity::Rare, 0),
	//	TPair<ERarity, int32>(ERarity::Epic, 0),
	//	TPair<ERarity, int32>(ERarity::Legendary, 0)
	//};

	//int32 rarities_size = FMath::Min(n, rarity_B.Num() + rarity_A.Num() + rarity_S.Num());

	//int32 i = 0;
	//while (i < rarities_size)
	//{
	//	constexpr int32 total_weight = 100;
	//	const int32 random_value = FMath::RandRange(0, total_weight);

	//	// Count up rarity based on the random value
	//	int32 cumulative_weight = 0;
	//	for (const auto& pair : weights)
	//	{
	//		cumulative_weight += pair.Value;
	//		if (random_value <= cumulative_weight)
	//		{
	//			int32 data_size;
	//			switch (pair.Key)
	//			{
	//			case ERarity::B:
	//				data_size = rarity_B.Num();
	//				break;

	//			case ERarity::A:
	//				data_size = rarity_A.Num();
	//				break;

	//			case ERarity::S:
	//				data_size = rarity_S.Num();
	//				break;

	//			default:
	//				data_size = 0;
	//				break;
	//			}
	//			// In order to return unique data, increase only when the data size is proper.
	//			if (rarity_count[pair.Key] < data_size)
	//			{
	//				rarity_count[pair.Key] += 1;
	//				++i;
	//			}
	//			break;
	//		}
	//	}
	//}

	//return rarity_count;
	return TMap<ERarity, int32>();
}

TArray<TPair<ERarity, int32>> URandomDataAssetsManager::GetRarityWeights(ERarity weight_rarity)
{
	// Weights for each rarity
	// Some of all weight should NOT be more than 100.
	TArray<TPair<ERarity, int32>> weights;
	switch (weight_rarity)
	{
	case ERarity::Common:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 80),
			TPair<ERarity, int32>(ERarity::Rare, 10),
			TPair<ERarity, int32>(ERarity::Epic, 5),
			TPair<ERarity, int32>(ERarity::Legendary, 5)
		};
		break;
	case ERarity::Rare:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 10),
			TPair<ERarity, int32>(ERarity::Rare, 75),
			TPair<ERarity, int32>(ERarity::Epic, 10),
			TPair<ERarity, int32>(ERarity::Legendary, 5)
		};
		break;
	case ERarity::Epic:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 5),
			TPair<ERarity, int32>(ERarity::Rare, 15),
			TPair<ERarity, int32>(ERarity::Epic, 75),
			TPair<ERarity, int32>(ERarity::Legendary, 5)
		};
		break;
	case ERarity::Legendary:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 10),
			TPair<ERarity, int32>(ERarity::Rare, 15),
			TPair<ERarity, int32>(ERarity::Epic, 25),
			TPair<ERarity, int32>(ERarity::Legendary, 50)
		};
		break;
	default:
		break;
	}

	return weights;
}
