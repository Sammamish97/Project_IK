/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.2.2025
Summary : Header file for Reward Container Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/WrapperEquipmentData.h"
#include "RewardContainerWidget.generated.h"

class UInventorySlot;
class UHorizontalBox;

UCLASS()
class PROJECT_IK_API URewardContainerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void LoadSelectedRewards(const FWrapperEquipmentData& rewards );
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> container_;

	UPROPERTY()
	TArray<TObjectPtr<UInventorySlot>> reward_slots_;

	UPROPERTY()
	FWrapperEquipmentData reward_cache_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UWeaponSlotWidget> weapon_slot_widget_class_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UActiveSkillSlotWidget> active_skill_slot_widget_class_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UPassiveSkillSlotWidget> passive_skill_slot_widget_class_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class URuneSlotWidget> rune_slot_widget_class_;
	
	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	// TSubclassOf<class URuneSlotWidget> support_skill_slot_widget_class_;
};
