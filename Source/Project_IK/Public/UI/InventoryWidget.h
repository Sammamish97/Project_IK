/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "Structs/WeaponStatusData.h"
#include "Structs/WrapperEquipmentData.h"
#include "InventoryWidget.generated.h"

class UStatusWidget;
class USupportSkillSlotWidget;
class URewardContainerWidget;
class UButton;
class UEquipSlot;
class UInventoryManager;
class UHeroEquipBoardWidget;
class URuneBoardWidget;
class UWidgetSwitcher;
class UInventorySlot;
class UBasicPopupWidget;

UCLASS(Blueprintable)
class PROJECT_IK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable)
	void InitInventoryWidget(int32 available_passive_skill_amount);

	UFUNCTION(BlueprintCallable)
	void UpdateInventoryData();

	UFUNCTION()
	void UpdateSetBonusEffect();

	UFUNCTION()
	void AddToRewardContainer(UInventorySlot* slot_ptr);
	
	UFUNCTION()
	void RemoveFromRewardContainer(UInventorySlot* slot_ptr);

	UFUNCTION()
	bool CheckDuplicatedActiveSkill(EActiveSkillType type);

	UFUNCTION()
	bool CheckDuplicatedPassiveSkill(EHeroType hero_type, EPassiveSkillType type);

	void LoadSelectedRewards(const FWrapperEquipmentData& rewards);

	void CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, const FWeaponStatusData& data);
	void CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down);
	void CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail);
	void CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, ERuneSetType rune_set_type);

	void SetPopupWidgetPos(FVector2D pos);
	void RemovePopupWidget();

	void SetHighlightVisibility(EGearType type, ESlateVisibility visibility);
	void SetHighlightVisibility(int32 rune_idx, ESlateVisibility visibility);
	void RemoveHighlight();

private:
	UFUNCTION()
	void OnHero_0_Board_Clicked();
	
	UFUNCTION()
	void OnHero_1_Board_Clicked();
	
	UFUNCTION()
	void OnHero_2_Board_Clicked();
	
	UFUNCTION()
	void OnHero_3_Board_Clicked();

	UFUNCTION()
	void OnConfirm();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_3_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> rune_status_switcher_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardWidget> rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStatusWidget> status_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URewardContainerWidget> reward_container_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> passive_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> active_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> weapon_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> rune_popup_class_;

	UPROPERTY()
	TObjectPtr<UBasicPopupWidget> equip_popup_ptr_;

	EGearType last_highlighted_gear_type = EGearType::INVALID;
};
