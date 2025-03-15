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
#include "WorldSettings/IKGameInstance.h"
#include "Subsystems/LevelTransitionSubsystem.h"

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
}

void URuneBoardWidget::InitBoardData(TObjectPtr<URuneStorageWidget> storage_ptr)
{
	for (int i = 0; i < 6; ++i)
	{
		slot_array_[i]->InitRuneStorageData(storage_ptr);
		slot_array_[i]->InitRuneBoardData(this);
	}
}

void URuneBoardWidget::LoadRuneBoardWidget(int32 hero_idx)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx);
		for (int i = 0; i < data_cache.rune_data_.Num(); i++)
		{
			slot_array_[i]->SetRuneData(data_cache.rune_data_[i]);
			slot_array_[i]->SetImageTexture();

		}
	}
}

void URuneBoardWidget::UpdateRuneBoard(int32 hero_idx)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx);
		for (int i = 0; i < 6; ++i)
		{
			data_cache.rune_data_[i] = slot_array_[i]->GetRuneData();
		}
		transition_system->UpdateSpawnDataIdx(hero_idx, data_cache);
	}
}

void URuneBoardWidget::ClearSelectedBorder()
{
	for (auto& elem:slot_array_)
	{
		elem->SetSelectedImageVisibility(false);
	}
}