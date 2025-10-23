/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Header file for main Widget in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Structs/WeaponData.h"
#include "Structs/ActiveSkillData.h"
#include "Structs/PassiveSkillData.h"
#include "Structs/RuneData.h"

#include "StoreWidget.generated.h"

enum class ERarity : uint8;
class UHorizontalBox;
class UTextBlock;
class UButton;
class UStoreSlot;
class UConfirmationWidget;
class UCreditWidget;
class UBasicPopupWidget;
class UTextManager;

UCLASS()
class PROJECT_IK_API UStoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	static constexpr int32 STOCK = 2;
	static constexpr int32 RUNE_STOCK = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UStoreSlot> store_widget_class_;

	void CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, const FWeaponStatusData& data);
	void CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down);
	void CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail);
	void CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, ERuneSetType rune_set_type);

	void RemovePopupWidget();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnPayButtonClicked();
	UFUNCTION()
	void OnStoreSlotClicked();

	int32 GetPriceByRarity(ERarity rarity);

	UFUNCTION()
	void GoToNextLevel();

private:
	template<typename ItemType, typename ItemContainer, typename SlotContainer>
	void AddItems(TArray<ItemType> items, ItemContainer& item_container, SlotContainer& slot_container);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FMargin slot_margin_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> weapon_slot_container_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> active_slot_container_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> passive_slot_container_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> rune_slot_container_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> total_cost_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> casher_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> pay_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> pay_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UConfirmationWidget> confirmation_widget_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCreditWidget> credit_widget_;

	UPROPERTY()
	TArray<TObjectPtr<UStoreSlot>> weapon_slots_;
	UPROPERTY()
	TArray<TObjectPtr<UStoreSlot>> active_slots_;
	UPROPERTY()
	TArray<TObjectPtr<UStoreSlot>> passive_slots_;
	UPROPERTY()
	TArray<TObjectPtr<UStoreSlot>> rune_slots_;

	TArray<FWeaponData> weapons_;
	TArray<FActiveSkillData> active_skills_;
	TArray<FPassiveSkillData> passive_skills_;
	TArray<FRuneData> runes_;

	int32 total_cost_;
	int32 credits_;

	//
	UPROPERTY()
	TObjectPtr<UTextManager> text_manager_cache_;

	UPROPERTY()
	TObjectPtr<UBasicPopupWidget> equip_popup_ptr_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> passive_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> active_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> weapon_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> rune_popup_class_;
};