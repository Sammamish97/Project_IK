/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Source file for Buff Container.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/BuffContainer.h"

#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "UI/BuffWidget.h"

void UBuffContainer::InitBuffContainer(UBuffPopupWidget* popup_widget)
{
	buff_popup_cache_ = popup_widget;
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};

	for(int32 i = 0; i < max_buffs_; ++i)
	{
		widget_array[i]->InitWidget(buff_popup_cache_, this);
		buff_container_->AddChild(widget_array[i]);
		if(widget_array[i]->IsWidgetAvailable())
		{
			widget_array[i]->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			widget_array[i]->SetVisibility(ESlateVisibility::Visible);
		}
		size_box_->SetHeightOverride(height_);
		widget_array[i]->size_box_->SetWidthOverride(height_);
		widget_array[i]->size_box_->SetHeightOverride(height_);
	}
}

void UBuffContainer::EnqueueBuff(EBuffType buff_type, UDisplayDataAsset* display_data, bool is_permanent, float duration)
{
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};
	//겹치는 버프 제거.
	UpdateQueue(buff_type);
	
	for(int32 i = 0; i < max_buffs_; ++i)
	{
		if(widget_array[i]->IsWidgetAvailable())
		{
			widget_array[i]->SetWidget(widget_array[i]->GetProgressBarStyle(), buff_type, display_data, is_permanent, duration, duration, false);
			widget_array[i]->BeginBuffUI();
			break;
		}
	}
	if (is_permanent == false)
	{
		FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UBuffContainer::UpdateQueue, buff_type);
		buff_timers_.FindOrAdd(buff_type);
		GetWorld()->GetTimerManager().SetTimer(buff_timers_[buff_type], expired_delegate, duration, false);
	}
}

void UBuffContainer::UpdateQueue(EBuffType buff_type)
{
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};
	int32 target_index = -1;
	for(int32 i = 0; i < max_buffs_; ++i)
	{
		if(widget_array[i]->IsWidgetAvailable() == false && widget_array[i]->GetCurBuffType() == buff_type)
		{
			target_index = i;
			break;
		}
	}
	if(target_index != -1)
	{
		for(int32 i = target_index; i < max_buffs_ - 1; ++i)
		{
			auto next_widget = widget_array[i + 1];
			widget_array[i]->SetWidget(next_widget->GetProgressBarStyle(), next_widget->GetCurBuffType(), next_widget->GetDisplayDataCache(), next_widget->GetIsPermanent(), next_widget->GetDuration(), next_widget->GetLeftTime(), next_widget->IsWidgetAvailable());
		}
		widget_array[max_buffs_ - 1]->ResetWidget();
	}
	if (buff_timers_.Contains(buff_type))
	{
		GetWorld()->GetTimerManager().ClearTimer(buff_timers_[buff_type]);
		buff_timers_.Remove(buff_type);
	}
}

void UBuffContainer::ClearBuffQueue()
{
}
