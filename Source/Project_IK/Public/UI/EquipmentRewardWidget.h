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

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> text_max_selectables_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UGridPanel> equipement_container_;

	UPROPERTY()
	TArray<TObjectPtr<UCheckboxButtonWidget>> candidates_items_widgets_;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	//TArray<> equipements_;
};
