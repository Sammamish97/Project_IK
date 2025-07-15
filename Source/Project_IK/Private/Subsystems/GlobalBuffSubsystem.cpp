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
	buff_lookup_.Empty();
	newly_added_buff_lookup_.Empty();
	everlasting_buff_.Empty();

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
		existing_index = newly_added_buff_lookup_.Find(buff_type);
		if (existing_index)
		{
			int32 index = newly_added_buff_lookup_[buff_type];
			buffs_[index].duration_ += buff_added.duration_;
		}


		int32 added_index = buffs_.Add(buff_added);

		newly_added_buff_lookup_.Add({ buff_type, added_index });
		if (buffs_[added_index].buff_logic_class_)
		{
			buff_logic_containers_.FindOrAdd(buff_type,
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
		buff_logic_containers_.Remove(buff_type);
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
		for (auto& pair : newly_added_buff_lookup_)
		{
			if (pair.Value > index_to_remove)
			{
				pair.Value -= 1;
			}
		}
		return true;
	}
	else
	{
		existing_index = newly_added_buff_lookup_.Find(buff_type);
		if (existing_index)
		{
			int32 index_to_remove = *existing_index;
			buff_logic_containers_.Remove(buff_type);
			buffs_.RemoveAt(index_to_remove);
			newly_added_buff_lookup_.Remove(buff_type);

			// Manually shrink them because they are custom indices.
			for (auto& pair : buff_lookup_)
			{
				if (pair.Value > index_to_remove)
				{
					pair.Value -= 1;
				}
			}
			for (auto& pair : newly_added_buff_lookup_)
			{
				if (pair.Value > index_to_remove)
				{
					pair.Value -= 1;
				}
			}
			return true;
		}
	}

	return false;
}

void UGlobalBuffSubsystem::ApplyBuff(UObject* buff_target)
{
	for (const FGlobalBuffData& buff : buffs_)
	{
		UGlobalBuffLogicBase* buff_logic = buff_logic_containers_[buff.buff_type_];
		if (buff_logic->IsBuffValidOnTarget(buff_target))
		{
			buff_logic->ApplyBuff(buff_target);
		}
	}

	for (EGlobalBuffType buff_type : everlasting_buff_)
	{
		UGlobalBuffLogicBase* buff_logic = buff_logic_containers_[buff_type];
		if (buff_logic->IsBuffValidOnTarget(buff_target))
		{
			buff_logic->ApplyBuff(buff_target);
		}
	}
}

bool UGlobalBuffSubsystem::HasBuff(EGlobalBuffType buff_type)
{
	return buff_lookup_.Contains(buff_type) || newly_added_buff_lookup_.Contains(buff_type) || everlasting_buff_.Contains(buff_type);
}

void UGlobalBuffSubsystem::ClearBuffs()
{
	for (const auto& [buff_type, index] : buff_lookup_)
	{
		buff_logic_containers_.Remove(buff_type);
	}
	for (const auto& [buff_type, index] : newly_added_buff_lookup_)
	{
		buff_logic_containers_.Remove(buff_type);
	}

	buff_lookup_.Empty();
	buffs_.Empty();
}

void UGlobalBuffSubsystem::UpdateBuffDurations()
{
	for (FGlobalBuffData& buff : buffs_)
	{
		if (!newly_added_buff_lookup_.Contains(buff.buff_type_))
		{
			buff.duration_ -= 1;
		}
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

	buff_lookup_.Append(newly_added_buff_lookup_);
	newly_added_buff_lookup_.Reset();
}

const TArray<FGlobalBuffData>& UGlobalBuffSubsystem::GetBuffs() const
{
	return buffs_;
}

void UGlobalBuffSubsystem::AddEverlastingBuff(EGlobalBuffType buff_type)
{
	everlasting_buff_.Add(buff_type);


	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	FGlobalBuffData buff_added = instance->GetDataTableManager()->GetGlobalBuffData(buff_type);

	if (buff_added.buff_logic_class_)
	{
		buff_logic_containers_.FindOrAdd(buff_type,
			NewObject<UGlobalBuffLogicBase>(this, buff_added.buff_logic_class_));
	}
}

const TSet<EGlobalBuffType> UGlobalBuffSubsystem::GetEverlastingBuffTypes() const
{
	return everlasting_buff_;
}
