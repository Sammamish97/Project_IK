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
#include "Structs/WrapperEquipmentData.h"
#include "InventoryWidget.generated.h"

class USupportSkillSlotWidget;
class URewardContainerWidget;
class UButton;
class UEquipSlot;
class UInventoryManager;
class UHeroEquipBoardWidget;
class URuneBoardWidget;
class UWidgetSwitcher;
class UInventorySlot;

UCLASS(Blueprintable)
class PROJECT_IK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable)
	void InitInventoryWidget();

	UFUNCTION(BlueprintCallable)
	void UpdateInventoryData();

	UFUNCTION()
	void UpdateSetBonusEffect();

	UFUNCTION()
	void AddToRewardContainer(UInventorySlot* slot_ptr);
	
	UFUNCTION()
	void RemoveFromRewardContainer(UInventorySlot* slot_ptr);

	UFUNCTION()
	bool CheckDuplicatedActiveSkill(const FActiveSkillData& skill_type);

	UFUNCTION()
	bool CheckDuplicatedSupportSkill(ESupportSkillType type);

	void LoadSelectedRewards(const FWrapperEquipmentData& rewards);

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
	TObjectPtr<USupportSkillSlotWidget> support_skill_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillSlotWidget> support_skill_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillSlotWidget> support_skill_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_3_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardWidget> rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URewardContainerWidget> reward_container_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;
};
