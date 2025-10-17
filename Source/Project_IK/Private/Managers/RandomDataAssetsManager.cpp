/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for a provider data assets randomly.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RandomDataAssetsManager.h"

#include "Managers/EnumCluster.h"

#include "Subsystems/RandomNumberGeneratorSubsystem.h"

ERarity URandomDataAssetsManager::GetRarityRandomly(ERarity weight_rarity, UWorld* world)
{
	TArray<TPair<ERarity, int32>> weights = GetRarityWeights(weight_rarity);

	int32 random_value = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, TOTAL_WEIGHT);

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
			TPair<ERarity, int32>(ERarity::Rare, 20),
			TPair<ERarity, int32>(ERarity::Legendary, 0)
		};
		break;
	case ERarity::Rare:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 15),
			TPair<ERarity, int32>(ERarity::Rare, 80),
			TPair<ERarity, int32>(ERarity::Legendary, 5)
		};
		break;
	case ERarity::Legendary:
		weights = {
			TPair<ERarity, int32>(ERarity::Common, 10),
			TPair<ERarity, int32>(ERarity::Rare, 30),
			TPair<ERarity, int32>(ERarity::Legendary, 60)
		};
		break;
	default:
		break;
	}

	return weights;
}
