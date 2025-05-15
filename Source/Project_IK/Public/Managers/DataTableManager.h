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

#include "DataTableManager.generated.h"

class UGlobalBuffDataAsset;
class UItemDataAsset;
class URandomDataAssetsManager;
class UStatInfoDataAsset;
class UCrowdControlInfoDataAsset;
class UTexture2D;
class UCharacterStatDataAsset;

struct FGlobalBuffData;
struct FRuneSetData;
struct FItemData;
struct FWrapperEquipmentData;
struct FCharacterData;
struct FWeaponData;
struct FPassiveSkillData;
struct FOopartData;
struct FRuneData;
struct FActiveSkillData;
struct FGlobalBuffData;

UCLASS(Blueprintable)
class PROJECT_IK_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
	FWeaponData GetWeaponData(EWeaponType type) const;
	FString WeaponEnumToString(EWeaponType weapon_type) const;
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

	FPassiveSkillData GetPassiveSkillData(EPassiveSkillType type) const;
	FString PassiveSkillEnumToString(EPassiveSkillType weapon_type) const;
	FPassiveSkillData GetPassiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FPassiveSkillData> GetUniquePassiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FActiveSkillData GetActiveSkillData(EActiveSkillType type) const;
	FString ActiveSkillEnumToString(EActiveSkillType weapon_type) const;
	FActiveSkillData GetActiveSkillDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FActiveSkillData> GetUniqueActiveSkillDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FOopartData GetOopartData(EOopartType type) const;
	FString OopartEnumToString(EOopartType oopart_type) const;
	FOopartData GetOopartDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FOopartData> GetUniqueOopartDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	FItemData GetItemData(EItemType type) const;
	FString ItemEnumToString(EItemType item_type) const;
	FItemData GetItemDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	TArray<FItemData> GetUniqueItemDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	const FCharacterData& GetCharacterData(EHeroType hero_type) const;
	FString HeroEnumToString(EHeroType hero_type) const;

	void EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount);
	void DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float decrease_amount);

	FGlobalBuffData GetGlobalBuffData(EGlobalBuffType buff_type) const;

	FWrapperEquipmentData GetEquipmentDataRandomly(ERarity weight_rarity = ERarity::Common) const;
	FWrapperEquipmentData GetUniqueEquipmentDataRandomly(int32 n = 1, ERarity weight_rarity = ERarity::Common) const;

	UTexture2D* GetStatTexture(ECharacterStatType stat_type);
	UTexture2D* GetCCTexture(ECCType cc_type);

	TSoftObjectPtr<UAnimMontage> GetUnitWeaponAnimMontage(EUnitBoneType bone, EWeaponAnimationType weapon, EWeaponAction action);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponDataAsset> weapon_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPassiveSkillDataAsset> passive_skill_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UActiveSkillDataAsset> active_skill_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UOopartDataAsset> oopart_data_asset_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterStatDataAsset> character_stat_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URuneDataAsset> rune_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GlobalBuffs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGlobalBuffDataAsset> global_buff_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UItemDataAsset> item_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatInfoDataAsset> stat_info_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCrowdControlInfoDataAsset> cc_info_data_asset_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWeaponAnimDataAsset> unit_weapon_anim_asset_;
};
