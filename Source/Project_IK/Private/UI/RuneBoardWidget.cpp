/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RuneBoardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/SpawnData.h"
#include "UI/RuneSlotWidget.h"
#include "UI/RuneStorageWidget.h"
#include "Components/ProgressBar.h"
#include "WorldSettings/IKGameInstance.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Managers/SetBonusManager.h"

void URuneBoardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	slot_array_.Empty();
	
	slot_array_.Add(slot_0_);
	slot_array_.Add(slot_1_);
	slot_array_.Add(slot_2_);
	slot_array_.Add(slot_3_);
	slot_array_.Add(slot_4_);
	slot_array_.Add(slot_5_);

	for (int i = 0; i < 6; ++i)
	{
		slot_array_[i]->SetRuneData(FRuneData(i));
		slot_array_[i]->SetIsBoardSlot(true);
	}
	slot_array_[0]->SetSelectedImageVisibility(true);
	
	line_array_.Add(line_0_);
	line_array_.Add(line_1_);
	line_array_.Add(line_2_);
	line_array_.Add(line_3_);
	line_array_.Add(line_4_);
	line_array_.Add(line_5_);
	line_array_.Add(line_6_);
	line_array_.Add(line_7_);
	line_array_.Add(line_8_);
	line_array_.Add(line_9_);
	line_array_.Add(line_10_);
	line_array_.Add(line_11_);
}

void URuneBoardWidget::InitBoardData(TObjectPtr<URuneStorageWidget> storage_ptr)
{
	for (int i = 0; i < 6; ++i)
	{
		slot_array_[i]->InitRuneStorageData(storage_ptr);
		slot_array_[i]->InitRuneBoardData(this);
	}
}

void URuneBoardWidget::LoadRuneBoardWidget()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx_cache_);
		for (int i = 0; i < data_cache.rune_data_.Num(); i++)
		{
			if (data_cache.rune_data_[i].is_empty == false)
			{
				slot_array_[i]->SetRuneData(data_cache.rune_data_[i].rune_data);
				slot_array_[i]->SetImageTexture();
			}
		}
	}
}

void URuneBoardWidget::UpdateRuneBoard()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx_cache_);
		for (int i = 0; i < 6; ++i)
		{
			data_cache.rune_data_[i] = slot_array_[i]->GetRuneSlotData();
		}
		transition_system->UpdateSpawnDataIdx(hero_idx_cache_, data_cache);
	}
}

void URuneBoardWidget::ClearSetBonusEffect()
{
	for (auto& elem : line_array_)
	{
		elem->SetPercent(0);
	}
}

void URuneBoardWidget::TurnOnSetBonusEffect()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<USetBonusManager> set_bonus_cache = ik_instance->GetSetBonusManager();
	
	TArray<FRuneData> data_array;
	for (int i = 0; i < 6; ++i)
	{
		data_array.Add(slot_array_[i]->GetRuneData());
	}
	auto result = set_bonus_cache->FigureOutRuneSet(data_array);
	for (const auto& elem : result)
	{
		if (elem.Value.Num() == 2)
		{
			line_array_[elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 3)
		{
				line_array_[6 + 3 * elem.Value[0]]->SetPercent(1.0);
				line_array_[7 + 3 * elem.Value[0]]->SetPercent(1.0);
				line_array_[8 + 3 * elem.Value[0]]->SetPercent(1.0);
		}
		else if (elem.Value.Num() == 6)
		{
			for (int i = 0; i < 6; ++i)
			{
				line_array_[i]->SetPercent(1.0);
			}
		}
	}
}

void URuneBoardWidget::ClearSelectedBorder()
{
	for (auto& elem:slot_array_)
	{
		elem->SetSelectedImageVisibility(false);
	}
}

void URuneBoardWidget::SetCurHeroIdx(int32 hero_idx)
{
	hero_idx_cache_ = hero_idx;
}
