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

	TArray<FWeaponData> weapons_;
	TArray<FActiveSkillData> active_skills_;
	TArray<FPassiveSkillData> passive_skills_;
	TArray<FRuneData> runes_;

	FWrapperEquipmentData& operator+=(const FWrapperEquipmentData& rhs)
	{
		weapons_.Append(rhs.weapons_);
		active_skills_.Append(rhs.active_skills_);
		passive_skills_.Append(rhs.passive_skills_);
		runes_.Append(rhs.runes_);

		return *this;
	}

	FWrapperEquipmentData& operator+=(const FWeaponData& rhs)
	{
		weapons_.Add(rhs);

		return *this;
	}

	FWrapperEquipmentData& operator+=(const FActiveSkillData& rhs)
	{
		active_skills_.Add(rhs);

		return *this;
	}

	FWrapperEquipmentData& operator+=(const FPassiveSkillData& rhs)
	{
		passive_skills_.Add(rhs);

		return *this;
	}

	FWrapperEquipmentData& operator+=(const FRuneData& rhs)
	{
		runes_.Add(rhs);

		return *this;
	}

	bool IsEmpty() const
	{
		return weapons_.IsEmpty() && active_skills_.IsEmpty() && passive_skills_.IsEmpty() && runes_.IsEmpty();
	}
};