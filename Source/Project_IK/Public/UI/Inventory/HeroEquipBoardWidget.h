/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Header file for Hero Equip Board Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "Structs/HeroData.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "HeroEquipBoardWidget.generated.h"

class UPassiveSkillSlotWidget;
class UWeaponSlotWidget;
class UActiveSkillSlotWidget;
class UInventorySlot;
class UInventoryWidget;
class UButton;
class UImage;

UCLASS()
class PROJECT_IK_API UHeroEquipBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	friend UInventoryWidget;
	
public:
	bool CheckDuplicatedPassiveSkill(EPassiveSkillType type);
	void InitHeroEquipBoard(UInventoryWidget* widget_ptr, EHeroType hero_type, const FHeroData& hero_data);
	void LoadHeroData();
	void UpdateHeroData();
	void SetAvailablePassiveSkillAmount(int32 amount);
	void ToggleReadOnly(bool is_read_only);
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWeaponSlotWidget> weapon_slot_;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UActiveSkillSlotWidget> active_skill_slot_;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UPassiveSkillSlotWidget> passive_skill_1_slot_;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UPassiveSkillSlotWidget> passive_skill_2_slot_;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UPassiveSkillSlotWidget> passive_skill_3_slot_;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> button_;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> hero_portrait_;

	UPROPERTY(Transient)
	TObjectPtr<UInventoryWidget> inventory_widget_cache_;

	EHeroType hero_type_ = EHeroType::INVALID;
};
