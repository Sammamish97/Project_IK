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
#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "UI/PopUps/BasicPopupWidget.h"
#include "UI/PopUps/GlobalBuffPopupWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UGlobalBuffWidget::InitGlobalBuffWidget(UBasicPopupWidget* popup_widget_ptr, FGlobalBuffData global_buff_data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
	global_buff_data_ = global_buff_data;
	image_->SetBrushFromTexture(global_buff_data_.thumbnail_);
	popup_widget_cache_ = popup_widget_ptr;
	left_duration_ = global_buff_data_.duration_;
}

void UGlobalBuffWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	popup_widget_cache_->UpdatePopupData(global_buff_data_.thumbnail_,
		text_manager_cache_->GetGlobalBuffNameText(global_buff_data_.buff_type_),
		text_manager_cache_->GetGlobalBuffDetailText(global_buff_data_.buff_type_));
	Cast<UGlobalBuffPopupWidget>(popup_widget_cache_)->UpdateLeftDuration(left_duration_);
}

void UGlobalBuffWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	popup_widget_cache_->ResetWidget();
}