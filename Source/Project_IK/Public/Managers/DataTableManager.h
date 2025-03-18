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
#include "Structs/OopartData.h"
#include "Structs/PassiveSkillData.h"
#include "Structs/WeaponData.h"
#include "Structs/CharacterData.h"
#include "Structs/RuneData.h"

#include "DataTableManager.generated.h"

class UGlobalBuffDataAsset;
enum class EGlobalBuffType : uint8;
struct FGlobalBuffData;

UCLASS(Blueprintable)
class PROJECT_IK_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
	FWeaponData GetWeaponData(EWeaponType type);
	FString WeaponEnumToString(EWeaponType weapon_type);

	class URuneSetDataAsset* GetRuneSetData(ERuneSetType type);
	FRuneData GetRuneData(ERuneSetType type, int slot_num);
	UTexture2D* GetRuneSetThumbnail(ERuneSetType type);
	
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

	FGlobalBuffData GetGlobalBuffData(EGlobalBuffType buff_type);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponDataAsset> weapon_data_asset_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* passive_skill_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* active_skill_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* oopart_table_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	UDataTable* character_table_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<class URuneDataAsset> rune_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GlobalBuffs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGlobalBuffDataAsset> global_buff_data_asset_;
};
