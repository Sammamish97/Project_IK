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
#include "UI/BuffWidget.h"

void UBuffContainer::NativeConstruct()
{
	Super::NativeConstruct();
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};

	for(int32 i = 0; i < max_buffs_; ++i)
	{
		widget_array[i]->InitWidget(i, this);
		widget_array[i]->SetVisibility(ESlateVisibility::Hidden);
		buff_container_->AddChild(widget_array[i]);
	}
}

void UBuffContainer::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBuffContainer::EnqueueBuff(FBuffData buff_data)
{
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};
	//겹치는 버프 제거.
	UpdateQueue(buff_data.buff_type_);
	
	for(int32 i = 0; i < max_buffs_; ++i)
	{
		if(widget_array[i]->IsWidgetAvailable())
		{
			widget_array[i]->BeginBuffUI(buff_data);
			break;
		}
	}
}

void UBuffContainer::UpdateQueue(EBuffType remove_target_type)
{
	TArray widget_array = {buff_widget_0_, buff_widget_1_, buff_widget_2_, buff_widget_3_, buff_widget_4_};
	int32 target_index = -1;
	for(int32 i = 0; i < max_buffs_; ++i)
	{
		if(widget_array[i]->IsWidgetAvailable() == false && widget_array[i]->GetBuffDataCache().buff_type_ == remove_target_type)
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
			widget_array[i]->SetWidget(next_widget->GetProgressBarStyle(), next_widget->GetBuffDataCache(), next_widget->GetLeftTime(), next_widget->IsWidgetAvailable());
		}
		widget_array[max_buffs_ - 1]->ResetWidget();
	}
}

void UBuffContainer::ClearBuffQueue()
{
}
