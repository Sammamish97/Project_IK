/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.8.2025
Summary : Source file for the Status Data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/RuneMechanics.h"
#include "Characters/HeroBase.h"

#include "Abilities/SetBonuses/SetBonusBase.h"
#include "Managers/SetBonusManager.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"

// Sets default values for this component's properties
URuneMechanics::URuneMechanics()
{
	PrimaryComponentTick.bCanEverTick = false;
	rune_slots_.AddDefaulted(6);
}

// Called when the game starts
void URuneMechanics::BeginPlay()
{
	Super::BeginPlay();
	bonus_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetSetBonusManager();
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
	hero_cache_ = GetOwner<AHeroBase>();
}

void URuneMechanics::EquipRune(ERuneSetType set_type, int32 idx)
{
	rune_slots_[idx] = data_table_cache_->GetRuneData(set_type, idx);
}

FStatusData URuneMechanics::GetTotalStatus()
{
	FStatusData total_status;
	for (int i = 0; i < rune_slots_.Num(); i++)
	{
		total_status += rune_slots_[i].rune_status;
	}
	return total_status;
}

//세트 보너스가 적용되는 시점은 전투레벨의 Begin Play이후이다.
void URuneMechanics::ApplySetBonuses()
{
	auto set_result = FigureOutRuneSet();
	for (int i = 0; i < set_result.Num(); i++)
	{
		bonus_manager_cache_->GetSetBonus(set_result[i].Key)->ActivateSetBonus(hero_cache_, set_result[i].Value.Num());
	}
}

TArray<TPair<ERuneSetType, TArray<int32>>> URuneMechanics::FigureOutRuneSet()
{
	TArray<TPair<ERuneSetType, TArray<int32>>> bonus_result;
	//1. 육각형 체크
	if (rune_slots_[0].set_type != ERuneSetType::INVALID)
	{
		if (rune_slots_[0].set_type == rune_slots_[1].set_type
			&& rune_slots_[1].set_type == rune_slots_[2].set_type
			&& rune_slots_[2].set_type == rune_slots_[3].set_type
			&& rune_slots_[3].set_type == rune_slots_[4].set_type
			&& rune_slots_[4].set_type == rune_slots_[5].set_type)
		{
			bonus_result.Add({rune_slots_[0].set_type, TArray<int32>{0, 1, 2, 3, 4, 5}});
			return bonus_result;
		}
	}
	
	// 2. 정삼각/역삼각 체크
	bool triangle_exist = false;
	if (rune_slots_[0].set_type == rune_slots_[2].set_type && rune_slots_[2].set_type == rune_slots_[4].set_type)
	{
		triangle_exist = true;
		bonus_result.Add({rune_slots_[0].set_type, TArray<int32>{0, 2, 4}});
	}
	if (rune_slots_[1].set_type == rune_slots_[3].set_type && rune_slots_[3].set_type == rune_slots_[5].set_type)
	{
		triangle_exist =true;
		bonus_result.Add({rune_slots_[1].set_type, TArray<int32>{1, 3, 5}});

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
		if (rune_slots_[i].set_type == rune_slots_[(i + 1) % 6].set_type && rune_slots_[i].set_type == rune_slots_[(i + 2) % 6].set_type) {
			skip[i] = skip[(i + 1) % 6] = skip[(i + 2) % 6] = true;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (!skip[i] && rune_slots_[i].set_type == rune_slots_[(i + 1) % 6].set_type)
		{
			bonus_result.Add({rune_slots_[i].set_type, TArray<int32>{i, (i + 1) % 6}});
		}
	}

	return bonus_result;
}

FString URuneMechanics::RuneEnumToString(ERuneSetType set_type)
{
	FString output;
	switch (set_type)
	{
	case ERuneSetType::ThunderLord:
		output = "ThunderLord";
		break;
	case ERuneSetType::Chariot:
		output = "Chariot";
		break;
	case ERuneSetType::INVALID:
		output = "INVALID";
		break;
	}
	return output;
}