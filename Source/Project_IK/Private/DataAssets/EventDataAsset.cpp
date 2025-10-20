/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.30.2025
Summary : Source file for Event Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/EventDataAsset.h"

#include "Subsystems/RandomNumberGeneratorSubsystem.h"

FEventData UEventDataAsset::GetActiveSkillData(EEventType type)
{
	checkf(event_data_map.Find(type), TEXT("Can't find Active Skill Type in the active skill data map!"));
	return event_data_map[type];	
}

FEventData UEventDataAsset::GetActiveSkillDataRandomly(UWorld* world, bool only_positive)
{
	TArray event_type_array = {EEventType::AirStrike, EEventType::Ambush, EEventType::Trap, EEventType::EMP, EEventType::ProtocolSurvive, EEventType::ProtocolAssault, EEventType::ProtocolEfficiency, EEventType::AbandonedSupply, EEventType::Recon, EEventType::SetTrap, EEventType::Core, EEventType::Patrol};
	int32 rand_idx;
	if (only_positive)
	{
		rand_idx = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(4, event_type_array.Num() - 1);
	}
	else
	{
		rand_idx = URandomNumberGeneratorSubsystem::GetRNG(world).RandRange(0, event_type_array.Num() - 1);
	}
	EEventType rand_type= event_type_array[rand_idx];
	return GetActiveSkillData(rand_type);
}
