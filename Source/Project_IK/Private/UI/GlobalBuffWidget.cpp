/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.26.2025
Summary : Source file for Global Buff Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/GlobalBuffWidget.h"

#include "Components/Image.h"
#include "DataAssets/DisplayDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "UI/PopUps/BasicPopupWidget.h"
#include "UI/PopUps/GlobalBuffPopupWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UGlobalBuffWidget::InitGlobalBuffWidget(UDisplayDataAsset* display_data, UBasicPopupWidget* popup_widget_ptr,
	int32 left_duration)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
	display_data_cache_ = display_data;
	image_->SetBrushFromTexture(display_data_cache_->thumbnail);
	popup_widget_cache_ = popup_widget_ptr;
	left_duration_ = left_duration;
}

void UGlobalBuffWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	popup_widget_cache_->UpdatePopupData(display_data_cache_->thumbnail,
		text_manager_cache_->GetActiveSkillNameText(display_data_cache_->text_key_),
		text_manager_cache_->GetActiveSkillDetailText(display_data_cache_->text_key_));
	Cast<UGlobalBuffPopupWidget>(popup_widget_cache_)->UpdateLeftDuration(left_duration_);
}

void UGlobalBuffWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	popup_widget_cache_->ResetWidget();
}