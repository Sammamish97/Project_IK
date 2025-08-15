/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.8.2025
Summary : Source file for a subsystem that manages perk progresses.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/PerkProgressSubsystem.h"

#include "Managers/EnumCluster.h"

void UPerkProgressSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);

	//for (int32 i = 0; i < 20; i++)
	//{
	//	AddProgress(i);
	//}
}

void UPerkProgressSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

const TSet<int32>& UPerkProgressSubsystem::GetProgress() const
{
	return progress_;
}

bool UPerkProgressSubsystem::AddProgress(int32 progress)
{
	if (progress_.Contains(progress))
	{
		return false;
	}
	else
	{
		progress_.Add(progress);
		return true;
	}
}
