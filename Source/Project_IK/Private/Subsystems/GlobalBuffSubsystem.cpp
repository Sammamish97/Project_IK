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

void UGlobalBuffSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGlobalBuffSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGlobalBuffSubsystem::AddBuff(const FGlobalBuffData& buff)
{
	buffs_.Add(buff);
}

void UGlobalBuffSubsystem::ApplyBuff(UObject* object_applied)
{

}

void UGlobalBuffSubsystem::UpdateBuffDurations()
{
	for (FGlobalBuffData& buff : buffs_)
	{
		buff.duration_;
	}

	buffs_.RemoveAll([](const FGlobalBuffData& buff)
		{
			return buff.duration_ <= 0;
		});
}
