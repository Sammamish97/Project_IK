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

	progresses_.Add(EHeroType::Hero1, TSet<int32>());
	progresses_.Add(EHeroType::Hero2, TSet<int32>());
	progresses_.Add(EHeroType::Hero3, TSet<int32>());
	progresses_.Add(EHeroType::Hero4, TSet<int32>());
}

void UPerkProgressSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

const TSet<int32>& UPerkProgressSubsystem::GetProgress(EHeroType hero_type)
{
	return progresses_[hero_type];
}

bool UPerkProgressSubsystem::AddProgress(EHeroType hero_type, int32 progress)
{
	if (progresses_.Contains(hero_type))
	{
		if (progresses_[hero_type].Contains(progress))
		{
			return false;
		}
		else
		{
			progresses_[hero_type].Add(progress);
			return true;
		}
	}
	return false;
}
