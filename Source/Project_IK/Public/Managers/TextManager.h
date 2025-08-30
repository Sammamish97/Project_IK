/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.5.2025
Summary : Header file for Text Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Internationalization/StringTable.h"
#include "Structs/CharacterData.h"
#include "TextManager.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API UTextManager : public UObject
{
	GENERATED_BODY()
public:
	FText GetActiveSkillNameText(const FString& key) const;
	FText GetActiveSkillDetailText(const FString& key) const;

	FText GetPassiveSkillNameText(const FString& key) const;
	FText GetPassiveSkillDetailText(const FString& key) const;

	FText GetSupportSkillNameText(const FString& key) const;
	FText GetSupportSkillDetailText(const FString& key) const;

	FText GetPerkNameText(const FString& key) const;
	FText GetPerkDetailText(const FString& key) const;

	FText GetRuneNameText(ERuneSetType set_type) const;
	FText GetRuneSetBonusText(ERuneSetType set_type, ERuneSetBonusType bonus_type) const;

	FText GetStatusText(ECharacterStatType stat_type) const;
	FText GetPopUpText(const FString& key) const;

	FText GetBuffNameText(EBuffType stat_type) const;
	FText GetBuffDetailText(EBuffType stat_type) const;

	FText GetGlobalBuffNameText(EGlobalBuffType stat_type) const;
	FText GetGlobalBuffDetailText(EGlobalBuffType stat_type) const;

	FText GetEventNameText(EEventType event_type) const;
	FText GetEventDetailText(EEventType event_type) const;
	FText GetEventOptionText(EEventType event_type, int32 option_idx) const;

private:
	FString ActiveSkillEnumToKey(EActiveSkillType active_skill_type);
	FString PassiveSkillEnumToKey(EActiveSkillType active_skill_type);
	FString SupportSkillEnumToKey(EActiveSkillType active_skill_type);

	FString StatusEnumToKey(ECharacterStatType stat_type) const;
	FString BuffEnumToKey(EBuffType buff_type) const;
	FString GlobalBuffEnumToKey(EGlobalBuffType global_buff_type) const;
	FString EventEnumToKey(EEventType event_type) const;

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> active_skill_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> active_skill_detail_table_;

	//

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> passive_skill_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> passive_skill_detail_table_;

	//

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> support_skill_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> support_skill_detail_table_;

	//
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> perk_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> perk_detail_table_;

	//

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> status_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> popup_table_;

	//
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> buff_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> buff_detail_table_;

	//

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> global_buff_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> global_buff_detail_table_;

	//

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_name_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_detail_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_option_1_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_option_2_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_option_3_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> event_option_4_table_;
	
	//
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> rune_name_table_;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> rune_edge_bonus_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> rune_triangle_bonus_table_;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStringTable> rune_hexagon_bonus_table_;
};
