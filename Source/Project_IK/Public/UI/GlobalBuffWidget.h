/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.26.2025
Summary : Header file for Global Buff Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalBuffWidget.generated.h"
class UBasicPopupWidget;
class UDisplayDataAsset;
class UTextManager;
class UImage;

UCLASS()
class PROJECT_IK_API UGlobalBuffWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitGlobalBuffWidget(UDisplayDataAsset* display_data, UBasicPopupWidget* popup_widget_ptr, int32 left_duration);
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UTextManager> text_manager_cache_;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> image_;

	UPROPERTY()
	TObjectPtr<UDisplayDataAsset> display_data_cache_;

	UPROPERTY()
	TObjectPtr<UBasicPopupWidget> popup_widget_cache_;

	UPROPERTY()
	int32 left_duration_;
};
