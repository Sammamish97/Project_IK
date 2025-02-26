/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the equip manager.

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
#include "Structs/PassiveSkillData.h"
#include "Structs/TrinketData.h"
#include "Structs/WeaponData.h"
#include "Structs/CharacterData.h"

#include "DataTableManager.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
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

	FCharacterData* GetCharacterData(EHeroType hero_type) const;
	FString HeroEnumToString(EHeroType hero_type) const;

	void EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount);
	void DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float decrease_amount);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* armor_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* trinket_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* weapon_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* passive_skill_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* active_skill_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* oopart_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* character_table_;
};
