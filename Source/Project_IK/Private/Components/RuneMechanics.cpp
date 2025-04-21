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
	switch (idx)
	{
		case 0:
			rune_data_1 = data_table_cache_->GetRuneData(set_type, idx);
			break;
		case 1:
			rune_data_2 = data_table_cache_->GetRuneData(set_type, idx);
			break;
		case 2:
			rune_data_3 = data_table_cache_->GetRuneData(set_type, idx);
			break;
		case 3:
			rune_data_4 = data_table_cache_->GetRuneData(set_type, idx);
			break;
		case 4:
			rune_data_5 = data_table_cache_->GetRuneData(set_type, idx);
			break;
		case 5:
			rune_data_6 = data_table_cache_->GetRuneData(set_type, idx);
		break;
	default:
		checkNoEntry()
	}
}

FStatusData URuneMechanics::GetTotalStatus()
{
	FStatusData total_status;
	for (const auto& elem : {rune_data_1, rune_data_2, rune_data_3, rune_data_4, rune_data_5, rune_data_6})
	{
		if (elem.IsSet())
		{
			total_status += elem.GetValue().rune_status;
		}
	}
	return total_status;
}

//세트 보너스가 적용되는 시점은 전투레벨의 Begin Play이후이다.
void URuneMechanics::ApplySetBonuses()
{
	auto set_result = bonus_manager_cache_->FigureOutRuneSet({rune_data_1, rune_data_2, rune_data_3, rune_data_4, rune_data_5, rune_data_6});
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
	case ERuneSetType::Chariot:
		output = "Chariot";
		break;

	case ERuneSetType::GreatBow:
		output = "GreatBow";
		break;

	case ERuneSetType::Viper:
		output = "Viper";
		break;

	case ERuneSetType::Dagger:
		output = "Dagger";
		break;
		
	case ERuneSetType::Poet:
		output = "Poet";
		break;

	case ERuneSetType::Tempest:
		output = "Tempest";
		break;
	}
	return output;
}