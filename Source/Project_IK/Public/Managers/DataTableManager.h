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
struct FSupportSkillData;
struct FPerkNode;

UCLASS(Blueprintable)
class PROJECT_IK_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
	FWeaponData GetWeaponStatusData(EWeaponType type) const;
	FWeaponData GetWeaponDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FWeaponData> GetUniqueWeaponDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FRuneSetData GetRuneSetData(ERuneSetType type) const;
	FRuneSetData GetRuneSetDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneSetData> GetRuneSetDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneSetData> GetUniqueRuneSetDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	FRuneData GetRuneData(ERuneSetType type, int slot_num) const;
	FRuneData GetRuneDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneData> GetRuneDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	TArray<FRuneData> GetUniqueRuneDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;
	UTexture2D* GetRuneSetThumbnail(ERuneSetType type) const;
	FText GetRuneSetBonusDetail(ERuneSetType set_type, ERuneBonusType bonus_type) const;

	FPassiveSkillData GetPassiveSkillData(EPassiveSkillType type) const;
	FPassiveSkillData GetPassiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FPassiveSkillData> GetUniquePassiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FActiveSkillData GetActiveSkillData(EActiveSkillType type) const;
	FActiveSkillData GetActiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FActiveSkillData> GetUniqueActiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FSupportSkillData GetSupportSkillData(ESupportSkillType type) const;
	FString SupportSkillEnumToString(ESupportSkillType weapon_type) const;
	FSupportSkillData GetSupportSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FSupportSkillData> GetUniqueSupportSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

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
	FSupportSkillData GetSupportSkillType(ESupportSkillType type);

	const TArray<FPerkNode>& GetTree() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class UWeaponDataAsset> weapon_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class UPassiveSkillDataAsset> passive_skill_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class UActiveSkillDataAsset> active_skill_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class USupportSkillDataAsset> support_skill_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class UCharacterStatDataAsset> character_stat_data_asset_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	TObjectPtr<class URuneDataAsset> rune_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GlobalBuffs")
	TObjectPtr<UGlobalBuffDataAsset> global_buff_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info")
	TObjectPtr<UStatInfoDataAsset> stat_info_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info")
	TObjectPtr<UCrowdControlInfoDataAsset> cc_info_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info")
	TObjectPtr<class UWeaponAnimDataAsset> unit_weapon_anim_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info")
	TObjectPtr<class UUnitTypeDataAsset> unit_type_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info")
	TObjectPtr<class USupportSkillDataAsset> support_skill_type_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PerkTree")
	TObjectPtr<UPerkTreeDataAsset> perk_tree_data_asset_;
};
