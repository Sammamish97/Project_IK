/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.11.2025
Summary : Source file for a subsystem that manages global buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/GlobalBuffSubsystem.h"

#include "Structs/GlobalBuff.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"

void UGlobalBuffSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGlobalBuffSubsystem::Deinitialize()
{
	// Clean up buff caches
	buffs_.Empty();
	buff_logic_containers_.Empty();

	Super::Deinitialize();
}

void UGlobalBuffSubsystem::AddBuff(EGlobalBuffType buff_type)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	FGlobalBuffData buff_added = instance->GetDataTableManager()->GetGlobalBuffData(buff_type);

	int32* existing_index = buff_lookup_.Find(buff_type);
	if (existing_index)
	{
		int32 index = buff_lookup_[buff_type];
		buffs_[index].duration_ += buff_added.duration_;
	}
	else
	{
		int32 added_index = buffs_.Add(buff_added);

		buff_lookup_.Add({ buff_type, added_index });
		if (buffs_[added_index].buff_logic_class_)
		{
			buff_logic_containers_.FindOrAdd(buffs_[added_index].buff_logic_class_,
				NewObject<UGlobalBuffLogicBase>(this, buffs_[added_index].buff_logic_class_));
		}
	}
}

bool UGlobalBuffSubsystem::RemoveBuff(EGlobalBuffType buff_type)
{
	int32* existing_index = buff_lookup_.Find(buff_type);
	if (existing_index)
	{
		int32 index_to_remove = *existing_index;
		buff_logic_containers_.Remove(buffs_[index_to_remove].buff_logic_class_);
		buffs_.RemoveAt(index_to_remove);
		buff_lookup_.Remove(buff_type);
		
		// Manually shrink them because they are custom indices.
		for (auto& pair : buff_lookup_)
		{
			if (pair.Value > index_to_remove)
			{
				pair.Value -= 1;
			}
		}
		return true;
	}

	return false;
}

void UGlobalBuffSubsystem::ApplyBuff(UObject* buff_target)
{
	for (const FGlobalBuffData& buff : buffs_)
	{
		TWeakObjectPtr<UGlobalBuffLogicBase> buff_logic = buff_logic_containers_[buff.buff_logic_class_];
		if (buff_logic->IsBuffValidOnTarget(buff_target))
		{
			buff_logic->ApplyBuff(buff_target);
		}
	}
}

bool UGlobalBuffSubsystem::HasBuff(EGlobalBuffType buff_type)
{
	int32* existing_index = buff_lookup_.Find(buff_type);
	return existing_index != nullptr;
}

void UGlobalBuffSubsystem::UpdateBuffDurations()
{
	for (FGlobalBuffData& buff : buffs_)
	{
		buff.duration_ -= 1;
	}


	for (int32 i = buffs_.Num() - 1; i >= 0; --i)
	{
		if (buffs_[i].duration_ <= 0)
		{
			buff_lookup_.Remove(buffs_[i].buff_type_);

			buffs_.RemoveAtSwap(i, 1, false);

			// If removed item is not the last element,
			if (i < buffs_.Num() - 1)
			{
				// Update buff_lookup_
				buff_lookup_[buffs_[i].buff_type_] = i;
			}
		}
	}
}

const TArray<FGlobalBuffData>& UGlobalBuffSubsystem::GetBuffs()
{
	return buffs_;
}
