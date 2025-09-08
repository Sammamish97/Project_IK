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
#include "Structs/PerkNode.h"
#include "DataTableManager.generated.h"

class UHeroDataAsset;
struct FHeroData;
class UGlobalBuffDataAsset;
class URandomDataAssetsManager;
class UStatInfoDataAsset;
class UCrowdControlInfoDataAsset;
class UTexture2D;
class UCharacterStatDataAsset;
class UPerkTreeDataAsset;

struct FGlobalBuffData;
struct FRuneSetData;
struct FWrapperEquipmentData;
struct FCharacterData;
struct FWeaponData;
struct FPassiveSkillData;
struct FRuneData;
struct FActiveSkillData;
struct FGlobalBuffData;
struct FPerkNode;

UCLASS(Blueprintable)
class PROJECT_IK_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
	FWeaponData GetWeaponData(EWeaponType type) const;
	FWeaponData GetWeaponDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	FWeaponData GetWeaponDataByRarity(ERarity rarity = ERarity::Common) const;
	TArray<FWeaponData> GetUniqueWeaponDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FRuneData GetRuneData(ERuneSetType type, int slot_num) const;
	FRuneData GetRuneDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneData> GetRuneDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneData> GetUniqueRuneDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	UTexture2D* GetRuneSetThumbnail(ERuneSetType type) const;

	FPassiveSkillData GetPassiveSkillData(EPassiveSkillType type) const;
	FPassiveSkillData GetPassiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FPassiveSkillData> GetPassiveSkillDataByRarity(int32 n = 1, ERarity rarity = ERarity::Common) const;
	TArray<FPassiveSkillData> GetUniquePassiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FActiveSkillData GetActiveSkillData(EActiveSkillType type) const;
	FActiveSkillData GetActiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	FActiveSkillData GetActiveSkillDataByRarity(ERarity rarity = ERarity::Common) const;
	TArray<FActiveSkillData> GetUniqueActiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	const FCharacterData& GetCharacterData(ECharacterType char_type) const;

	void EnhanceHeroesStatData(ECharacterStatType stat_type, float increase_amount);
	void DiminishHeroesStatData(ECharacterStatType stat_type, float decrease_amount);

	FGlobalBuffData GetGlobalBuffData(EGlobalBuffType buff_type) const;

	FWrapperEquipmentData GetEquipmentDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	FWrapperEquipmentData GetUniqueEquipmentDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	UTexture2D* GetStatTexture(ECharacterStatType stat_type);
	UTexture2D* GetCCTexture(ECCType cc_type);

	TSoftObjectPtr<UAnimMontage> GetUnitWeaponAnimMontage(EUnitBoneType bone, EWeaponAnimationType weapon, EWeaponAction action);
	TSoftObjectPtr<UAnimBlueprint> GetWeaponAnimInstance(EUnitBoneType bone, EWeaponAnimationType weapon);

	TSubclassOf<class AUnit> GetUnitType(ECharacterType type);

	const TArray<FPerkNode>& GetTree() const;

	FHeroData GetHeroData(EHeroType type) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UWeaponDataAsset> weapon_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UPassiveSkillDataAsset> passive_skill_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UActiveSkillDataAsset> active_skill_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCharacterStatDataAsset> character_stat_data_asset_;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class URuneDataAsset> rune_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGlobalBuffDataAsset> global_buff_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStatInfoDataAsset> stat_info_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCrowdControlInfoDataAsset> cc_info_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UWeaponAnimDataAsset> unit_weapon_anim_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UUnitTypeDataAsset> unit_type_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPerkTreeDataAsset> perk_tree_data_asset_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UHeroDataAsset> hero_data_asset_;
};
