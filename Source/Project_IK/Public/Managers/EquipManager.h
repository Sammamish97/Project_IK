/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "Structs/ActiveSkillData.h"
#include "Structs/ArmorData.h"
#include "Structs/OopartData.h"
#include "Structs/TrinketData.h"
#include "Structs/WeaponData.h"
#include "EquipManager.generated.h"

struct FPassiveSkillData;

UCLASS()
class PROJECT_IK_API UEquipManager : public UObject
{
	GENERATED_BODY()
public:
	UEquipManager();
	FArmorData GetArmorData(EArmorType type);
	FString ArmorEnumToString(EArmorType armor_type);

	FTrinketData GetTrinketData(ETrinketType type);
	FString TrinketEnumToString(ETrinketType trinket_type);

	FWeaponData GetWeaponData(EWeaponType type);
	FString WeaponEnumToString(EWeaponType weapon_type);

	FPassiveSkillData GetPassiveSkillData(EPassiveSkillType type);
	FString PassiveSkillEnumToString(EPassiveSkillType weapon_type);

	FActiveSkillData GetActiveSkillData(EActiveSkillType type);
	FString ActiveSkillEnumToString(EActiveSkillType weapon_type);

	FOopartData GetOopartData(EOopartType type);
	FString OopartEnumToString(EOopartType oopart_type);

private:
	UDataTable* armor_table_;
	UDataTable* trinket_table_;
	UDataTable* weapon_table_;
	UDataTable* passive_skill_table_;
	UDataTable* active_skill_table_;
	UDataTable* oopart_table_;
};
