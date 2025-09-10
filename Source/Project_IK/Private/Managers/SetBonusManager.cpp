/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Set Bonus Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/SetBonusManager.h"
#include "Abilities/SetBonuses/SetBonus_Chariot.h"
#include "Abilities/SetBonuses/SetBonus_Dagger.h"
#include "Abilities/SetBonuses/SetBonus_GreatBow.h"
#include "Abilities/SetBonuses/SetBonus_Quake.h"
#include "Abilities/SetBonuses/SetBonus_Tempest.h"
#include "Abilities/SetBonuses/SetBonus_Viper.h"

TObjectPtr<USetBonusBase> USetBonusManager::GetSetBonus(AActor* hero_ptr, ERuneSetType type)
{
	switch (type)
	{
	case ERuneSetType::Chariot:
		return NewObject<USetBonus_Chariot>(hero_ptr, chariot_);

	case ERuneSetType::GreatBow:
		return NewObject<USetBonus_GreatBow>(hero_ptr, great_bow_);

	case ERuneSetType::Viper:
		return NewObject<USetBonus_Viper>(hero_ptr, viper_);

	case ERuneSetType::Dagger:
		return NewObject<USetBonus_Dagger>(hero_ptr, dagger_);

	case ERuneSetType::Tempest:
		return NewObject<USetBonus_Tempest>(hero_ptr, tempest_);

	case ERuneSetType::Quake:
		return NewObject<USetBonus_Quake>(hero_ptr, quake_);
	}
	return nullptr;
}

TOptional<RuneSetBonus> USetBonusManager::FigureOutHexagonSet(
	const TArray<FRuneData>& rune_slots)
{
	bool is_all_equipped = true;
	for (int32 i = 0; i < rune_slots.Num(); i++)
	{
		if (rune_slots[i].set_type == ERuneSetType::INVALID)
		{
			is_all_equipped = false;
		}
	}

	if (is_all_equipped)
	{
		bool is_all_same_type = true;
		for (int32 i = 0; i < rune_slots.Num(); i++)
		{
			if (rune_slots[0].set_type != rune_slots[i].set_type)
			{
				is_all_same_type = false;
			}
		}
		if (is_all_same_type && rune_slots[0].set_type != ERuneSetType::INVALID)
		{
			RuneSetBonus result = {rune_slots[0].set_type, TArray{0, 1, 2, 3, 4, 5}};
			return result;
		}
	}
	return NullOpt;
}

TOptional<RuneSetBonus> USetBonusManager::FigureOutTriangleSet(
	const TArray<FRuneData>& rune_slots, TArray<int32>& indices, TArray<int32>& inv_indices)
{
	float is_all_equipped = true;
	for (int32 i :  indices)
	{
		if (rune_slots[i].set_type == ERuneSetType::INVALID)
		{
			is_all_equipped = false;
		}
	}
	if (is_all_equipped)
	{
		bool is_all_same_type = true;
		for (int32 i : indices)
		{
			if (rune_slots[indices[0]].set_type != rune_slots[i].set_type)
			{
				is_all_same_type = false;
			}
		}
		for (int32 i : inv_indices)
		{
			if (rune_slots[i].set_type != ERuneSetType::INVALID)
			{
				if (rune_slots[indices[0]].set_type == rune_slots[i].set_type)
				{
					is_all_same_type = false;
				}
			}
		}
		if (is_all_same_type && rune_slots[indices[0]].set_type != ERuneSetType::INVALID)
		{
			RuneSetBonus result = {rune_slots[indices[0]].set_type, indices};
			return result;
		}
	}
	return NullOpt;
}

TArray<RuneSetBonus> USetBonusManager::FigureOutEdgeSet(
	const TArray<FRuneData>& rune_slots)
{
	TArray<RuneSetBonus> result;
	
	bool skip[6] = { false }; // 연속된 3개 이상이면 점수 제외하기 위한 배열

	//3개 이상 연속되는 index는 skip을 통해 이후 검사에서 제외.
	for (int i = 0; i < 6; i++) {
		if (rune_slots[i].set_type != ERuneSetType::INVALID && rune_slots[(i + 1) % 6].set_type != ERuneSetType::INVALID && rune_slots[(i + 2) % 6].set_type != ERuneSetType::INVALID)
		{
			if (rune_slots[i].set_type == rune_slots[(i + 1) % 6].set_type
				&&
				rune_slots[i].set_type == rune_slots[(i + 2) % 6].set_type) {
				skip[i] = skip[(i + 1) % 6] = skip[(i + 2) % 6] = true;
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (rune_slots[i].set_type != ERuneSetType::INVALID && rune_slots[(i + 1) % 6].set_type != ERuneSetType::INVALID)
		{
			if (skip[i] == false
				&&
				rune_slots[i].set_type != ERuneSetType::INVALID
				&&
				rune_slots[i].set_type == rune_slots[(i + 1) % 6].set_type)
			{
				result.Push({rune_slots[i].set_type, TArray{i, (i + 1) % 6}});
			}
		}
	}
	return result;
}

TArray<RuneSetBonus> USetBonusManager::FigureOutRuneSet(const TArray<FRuneData>& rune_slots)
{
	TArray<RuneSetBonus> bonus_result;
	auto hex_result = FigureOutHexagonSet(rune_slots);
	if (hex_result.IsSet())
	{
		bonus_result.Push(hex_result.GetValue());
		return bonus_result;
	}

	bool is_tri_set_exist = false;
	TArray tri_indices = {0, 2, 4};
	TArray inv_tri_indices = {1, 3, 5};
	auto tri_result = FigureOutTriangleSet(rune_slots, tri_indices, inv_tri_indices);
	if (tri_result.IsSet())
	{
		is_tri_set_exist = true;
		bonus_result.Push(tri_result.GetValue());
	}
	auto inv_tri_result =FigureOutTriangleSet(rune_slots, inv_tri_indices, tri_indices);
	if (inv_tri_result.IsSet())
	{
		is_tri_set_exist = true;
		bonus_result.Push(inv_tri_result.GetValue());
	}
	if (is_tri_set_exist == true)
	{
		return bonus_result;
	}
	
	return FigureOutEdgeSet(rune_slots);
}