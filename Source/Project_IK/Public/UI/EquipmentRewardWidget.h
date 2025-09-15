/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.08.2025
Summary : Header file for equipment reward widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CheckboxButtonWidget.h"
#include "Managers/EnumCluster.h"
#include "Structs/WeaponStatusData.h"
#include "EquipmentRewardWidget.generated.h"

class UUniformGridPanel;
class UHorizontalBox;
class URewardSelectWidget;
class UTextBlock;
class UGridPanel;
class UCheckboxButtonWidget;
class UButton;
class UBasicPopupWidget;
class UDataTableManager;

UCLASS()
class PROJECT_IK_API UEquipmentRewardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void IncreaseSelectedCounter();
	void DecreaseSelectedCounter();

	void CreateWeaponPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, const FWeaponStatusData& data);
	void CreateActiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, float cool_down);
	void CreatePassiveSkillPopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail);
	void CreateRunePopupWidget(UTexture2D* thumbnail, const FText& name, const FText& detail, ERuneSetType rune_set_type);

	void SetPopupWidgetPos(FVector2D pos);
	void RemovePopupWidget();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnConfirmButtonClicked();

	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<UTextBlock> text_max_selectables_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> reward_container_;

	UPROPERTY()
	TArray<TObjectPtr<URewardSelectWidget>> reward_widgets_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	int32 selected_amount_ = 0;
	int32 max_choice_ = 0;

	UPROPERTY()
	TObjectPtr<UBasicPopupWidget> equip_popup_ptr_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URewardSelectWidget> reward_widget_class_;

	//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> passive_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> active_skill_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> weapon_popup_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBasicPopupWidget> rune_popup_class_;
};