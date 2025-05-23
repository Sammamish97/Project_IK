/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.09.2025
Summary : Structure for wrapper class that contains equipment.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Structs/ActiveSKillData.h"
#include "Structs/PassiveSkillData.h"
#include "Structs/RuneData.h"
#include "Structs/WeaponData.h"
#include "WrapperEquipmentData.generated.h"

USTRUCT(BlueprintType)
struct FWrapperEquipmentData
{
	GENERATED_BODY()

public:
	TArray<FActiveSkillData> active_skills_;
	TArray<FPassiveSkillData> passive_skills_;
	TArray<FRuneData> runes_;
	TArray<FWeaponData> weapons_;
};