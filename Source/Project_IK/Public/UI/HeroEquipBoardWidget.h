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
	void InitHeroEquipBoard(UInventoryWidget* widget_ptr, EHeroType hero_type);
	void LoadHeroData();
	void UpdateHeroData();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipBoard", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWeaponSlotWidget> weapon_slot_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipBoard", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UActiveSkillSlotWidget> active_skill_slot_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipBoard", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UPassiveSkillSlotWidget> passive_skill_1_slot_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipBoard", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> button_;

	UPROPERTY(Transient)
	TObjectPtr<UInventoryWidget> inventory_widget_cache_;

	EHeroType hero_type_ = EHeroType::INVALID;
};
