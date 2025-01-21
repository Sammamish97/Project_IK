/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.06.2025
Summary : Source file for an abstract class that has helper functions related to handle assets have rarity.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RarityAbstractObject.h"
#include "Managers/EnumCluster.h"

ERarity URarityAbstractObject::GetRarityRandomly(ERarity weight_rarity) const
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
	return ERarity::B;
}

TMap<ERarity, int32> URarityAbstractObject::GetRaritiesRandomly(ERarity weight_rarity, int32 n) const
{
	TArray<TPair<ERarity, int32>> weights = GetRarityWeights(weight_rarity);


	TMap<ERarity, int32> rarity_count = {
		TPair<ERarity, int32>(ERarity::B, 0),
		TPair<ERarity, int32>(ERarity::A, 0),
		TPair<ERarity, int32>(ERarity::S, 0)
	};

	int32 rarities_size = FMath::Min(n, rarity_B.Num() + rarity_A.Num() + rarity_S.Num());

	int32 i = 0;
	while (i < rarities_size)
	{
		constexpr int32 total_weight = 100;
		const int32 random_value = FMath::RandRange(0, total_weight);

		// Count up rarity based on the random value
		int32 cumulative_weight = 0;
		for (const auto& pair : weights)
		{
			cumulative_weight += pair.Value;
			if (random_value <= cumulative_weight)
			{
				int32 data_size;
				switch (pair.Key)
				{
				case ERarity::B:
					data_size = rarity_B.Num();
					break;

				case ERarity::A:
					data_size = rarity_A.Num();
					break;

				case ERarity::S:
					data_size = rarity_S.Num();
					break;

				default:
					data_size = 0;
					break;
				}
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

void URarityAbstractObject::CategorizeByRarity(UDataTable* data_table)
{
	if (!data_table)
	{
		return;
	}

	for (auto& row_pair : data_table->GetRowMap())
	{
		FRarityData* item = reinterpret_cast<FRarityData*>(row_pair.Value);
		if (!item)
		{
			continue;
		}

		// Sort the item into the correct array based on its rarity
		switch (item->rarity_)
		{
		case ERarity::B:
			rarity_B.Add(item);
			break;
		case ERarity::A:
			rarity_A.Add(item);
			break;
		case ERarity::S:
			rarity_S.Add(item);
			break;
		default:
			break;
		}
	}
}

FRarityData* URarityAbstractObject::GetRandomDataByRarity(ERarity rarity) const
{
	int32 rand_index = 0;
	switch (rarity)
	{
	case ERarity::S:
		rand_index = FMath::RandRange(0, rarity_S.Num() - 1);
		return rarity_S[rand_index];
		break;
	case ERarity::A:
		rand_index = FMath::RandRange(0, rarity_A.Num() - 1);
		return rarity_A[rand_index];
		break;
	case ERarity::B:
	default:
		rand_index = FMath::RandRange(0, rarity_B.Num() - 1);
		return rarity_B[rand_index];
		break;
	}
}

TArray<FRarityData*> URarityAbstractObject::GetUniqueRandomData(TMap<ERarity, int32> rarity_count) const
{
	TArray<FRarityData*> return_data;

	const TArray<FRarityData*>* rarity_array = nullptr;

	for (const TPair<ERarity, int32>& count_pair : rarity_count)
	{
		switch (count_pair.Key)
		{
		case ERarity::B:
			rarity_array = &rarity_B;
			break;

		case ERarity::A:
			rarity_array = &rarity_A;
			break;

		case ERarity::S:
			rarity_array = &rarity_S;
			break;

		default:
			rarity_array = &rarity_B;
			break;
		}


		TArray<int32> indices;
		for (int32 i = 0; i < rarity_array->Num(); i++)
		{
			indices.Add(i);
		}

		// Shuffle index

		for (int32 i = indices.Num() - 1; i > 0; --i)
		{
			int32 shuffle_index = FMath::RandRange(0, i);
			if (i == shuffle_index)
			{
				continue;
			}
			indices.Swap(i, shuffle_index);
		}

		for (int32 i = 0; i < count_pair.Value; i++)
		{
			return_data.Add((*rarity_array)[indices[i]]);
		}
	}

	return return_data;
}

TArray<TPair<ERarity, int32>> URarityAbstractObject::GetRarityWeights(ERarity weight_rarity) const
{
	// Weights for each rarity
	TArray<TPair<ERarity, int32>> weights;
	switch (weight_rarity)
	{
	case ERarity::S:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 15),
			TPair<ERarity, int32>(ERarity::A, 35),
			TPair<ERarity, int32>(ERarity::S, 50)
		};
		break;
	case ERarity::A:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 20),
			TPair<ERarity, int32>(ERarity::A, 60),
			TPair<ERarity, int32>(ERarity::S, 20)
		};
		break;
	case ERarity::B:
		weights = {
			TPair<ERarity, int32>(ERarity::B, 60),
			TPair<ERarity, int32>(ERarity::A, 30),
			TPair<ERarity, int32>(ERarity::S, 10)
		};
		break;
	default:
		break;
	}

	return weights;
}
