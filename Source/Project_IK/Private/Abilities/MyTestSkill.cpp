/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Test skill class.
					The first skill class to test it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/MyTestSkill.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

UMyTestSkill::UMyTestSkill()
{
}

bool UMyTestSkill::ActivateSkill(const FTargetResult& TargetResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Skill executed in derived class! %s"), *TargetResult.target_location_.ToString());
	for (int32 i = 0; i < TargetResult.target_actors_.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected %ith actor name: %s"), i, *TargetResult.target_actors_[i]->GetName());
	}
	return true;
}
