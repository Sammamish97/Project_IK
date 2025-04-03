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
#include "Abilities/SetBonuses/SetBonusBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"

// Sets default values for this component's properties
URuneMechanics::URuneMechanics()
{
	PrimaryComponentTick.bCanEverTick = false;
	rune_slots_ = {rune_data_1 ,rune_data_2 ,rune_data_3, rune_data_4, rune_data_5, rune_data_6 };
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
		if (rune_slots_[i].IsSet())
		{
			total_status += rune_slots_[i].GetValue().rune_status;
		}
	}
	return total_status;
}

//세트 보너스가 적용되는 시점은 전투레벨의 Begin Play이후이다.
void URuneMechanics::ApplySetBonuses()
{
	auto set_result = bonus_manager_cache_->FigureOutRuneSet(rune_slots_);
	for (int i = 0; i < set_result.Num(); i++)
	{
		if (set_result[i].Key != ERuneSetType::INVALID)
		{
			set_bonus_cache_ = bonus_manager_cache_->GetSetBonus(set_result[i].Key);
			set_bonus_cache_->ActivateSetBonus(hero_cache_, set_result[i].Value.Num());
		}
	}
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