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
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

// Sets default values for this component's properties
URuneMechanics::URuneMechanics()
{
	PrimaryComponentTick.bCanEverTick = false;
	equipped_runes_.Init(FRuneData(), 6);
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
	equipped_runes_[idx] = data_table_cache_->GetRuneData(set_type, idx);
}

FStatusData URuneMechanics::GetTotalStatus()
{
	FStatusData total_status;
	for (int32 i = 0; i < 6; ++i)
	{
		if (equipped_runes_[i].set_type != ERuneSetType::INVALID)
		{
			for(const auto& stat : equipped_runes_[i].status_map)
			{
				total_status[stat.Key] += stat.Value;
			}
		}
	}
	return total_status;
}

//세트 보너스가 적용되는 시점은 전투레벨의 Begin Play이후이다.
void URuneMechanics::ApplySetBonuses()
{
	auto set_result = GetSetBonusData();
	for (int i = 0; i < set_result.Num(); i++)
	{
		if (set_result[i].Key != ERuneSetType::INVALID)
		{
			set_bonus_cache_ = bonus_manager_cache_->GetSetBonus(hero_cache_, set_result[i].Key);
			set_bonus_cache_->ActivateSetBonus(hero_cache_, set_result[i].Value.Num());
		}
	}
}

TArray<RuneSetBonus> URuneMechanics::GetSetBonusData()
{
	return bonus_manager_cache_->FigureOutRuneSet(equipped_runes_);
}

const TArray<FRuneData>& URuneMechanics::GetEquippedRunes()
{
	return equipped_runes_;
}