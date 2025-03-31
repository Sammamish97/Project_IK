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

TObjectPtr<USetBonusBase> USetBonusManager::GetSetBonus(ERuneSetType type)
{
	switch (type)
	{
	case ERuneSetType::Chariot:
		return NewObject<USetBonus_Chariot>(this);
		break;
	}
	return nullptr;
}


TArray<TPair<ERuneSetType, TArray<int32>>> USetBonusManager::FigureOutRuneSet(const TArray<FRuneData>& rune_data)
{
	TArray<TPair<ERuneSetType, TArray<int32>>> bonus_result;
	//1. 육각형 체크
	if (rune_data[0].set_type != ERuneSetType::INVALID)
	{
		if (rune_data[0].set_type == rune_data[1].set_type
			&& rune_data[1].set_type == rune_data[2].set_type
			&& rune_data[2].set_type == rune_data[3].set_type
			&& rune_data[3].set_type == rune_data[4].set_type
			&& rune_data[4].set_type == rune_data[5].set_type)
		{
			bonus_result.Add({rune_data[0].set_type, TArray<int32>{0, 1, 2, 3, 4, 5}});
			return bonus_result;
		}
	}
	
	// 2. 정삼각/역삼각 체크
	bool triangle_exist = false;
	if (rune_data[0].set_type == rune_data[2].set_type && rune_data[2].set_type == rune_data[4].set_type
		&&
		rune_data[1].set_type != rune_data[0].set_type &&
		rune_data[3].set_type != rune_data[0].set_type &&
		rune_data[5].set_type != rune_data[0].set_type
		)
	{
		if (rune_data[0].set_type != ERuneSetType::INVALID)
		{
			bonus_result.Add({rune_data[0].set_type, TArray<int32>{0, 2, 4}});
			triangle_exist = true;
		}
	}
	if (rune_data[1].set_type == rune_data[3].set_type && rune_data[3].set_type == rune_data[5].set_type
		&&
		rune_data[0].set_type != rune_data[1].set_type &&
		rune_data[2].set_type != rune_data[1].set_type &&
		rune_data[4].set_type != rune_data[1].set_type
		)
	{
		if (rune_data[1].set_type != ERuneSetType::INVALID)
		{
			triangle_exist =true;
			bonus_result.Add({rune_data[1].set_type, TArray<int32>{1, 3, 5}});
		}
	}
	if (triangle_exist)
	{
		//삼각형이 하나라도 존재하면, 그 어느 간선도 존재할 수 없음.
		return bonus_result;
	}

	//3. 이어진 간선 체크
	bool skip[6] = { false }; // 연속된 3개 이상이면 점수 제외하기 위한 배열

	//3개 이상 연속되는 index는 skip을 통해 이후 검사에서 제외.
	for (int i = 0; i < 6; i++) {
		if (rune_data[i].set_type == rune_data[(i + 1) % 6].set_type && rune_data[i].set_type == rune_data[(i + 2) % 6].set_type) {
			skip[i] = skip[(i + 1) % 6] = skip[(i + 2) % 6] = true;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (skip[i] == false && rune_data[i].set_type == rune_data[(i + 1) % 6].set_type)
		{
			if (rune_data[i].set_type != ERuneSetType::INVALID)
			{
				bonus_result.Add({rune_data[i].set_type, TArray<int32>{i, (i + 1) % 6}});
			}
		}
	}
	return bonus_result;
}