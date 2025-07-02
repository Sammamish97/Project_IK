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
#include "Structs/WrapperEquipmentData.h"
#include "Managers/InventoryManager.h"
#include "Blueprint/WidgetTree.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "UI/CheckboxButtonWidget.h"
#include "EquipmentRewardWidget.generated.h"

class UTextBlock;
class UGridPanel;
class UCheckboxButtonWidget;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UEquipmentRewardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	static constexpr int32 NUM_CANDIDATES = 6;
	static constexpr int32 MAX_CHOICE = 3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCheckboxButtonWidget> check_box_button_class_;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void PopulateCheckboxButtons();

	UFUNCTION()
	void OnConfirmButtonClicked();
	UFUNCTION()
	void OnCheckboxButtonClicked();

	bool ToggleCheckboxButton(UCheckboxButtonWidget* widget);

	template<typename Data>
	void CreateCheckboxButton(TArray<Data> data, int32& row, int32& column);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> text_max_selectables_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UGridPanel> equipment_container_;

	UPROPERTY()
	TArray<TObjectPtr<UCheckboxButtonWidget>> equipment_widgets_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	FWrapperEquipmentData equipments_;

	int32 checked_equipment_num_;
};

template<typename Data>
inline void UEquipmentRewardWidget::CreateCheckboxButton(TArray<Data> data_array, int32& row, int32& column)
{
	for (const Data& data : data_array)
	{
		UCheckboxButtonWidget* cb = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
		if (cb)
		{
			UGridSlot* slot = equipment_container_->AddChildToGrid(cb, row, column);
			if (slot)
			{
				slot->SetPadding(FMargin(64.f, 16.f));
			}
			cb->SetButtonTexture(data.item_data_.thumbnail);

			equipment_widgets_.Add(cb);
			column += 1;
		}
	}
}