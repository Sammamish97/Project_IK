/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Source file for Map Level HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/Map/IKMapHUD.h"

#include "Kismet/GameplayStatics.h"
#include "UI/InventoryWidget.h"
#include "WorldSettings/IKGameInstance.h"
#include "UI/GlobalBuffDisplayer.h"

void AIKMapHUD::BeginPlay()
{
	Super::BeginPlay();
	if (map_widget_class_)
	{
		map_widget_ = CreateWidget<UUserWidget>(GetWorld(), map_widget_class_);
		if (map_widget_)
		{
			map_widget_->AddToViewport();
		}
	}

	if (global_buff_displayer_class_)
	{
		global_buff_displayer_ = CreateWidget<UGlobalBuffDisplayer>(GetWorld(), global_buff_displayer_class_);
		if (global_buff_displayer_)
		{
			global_buff_displayer_->AddToViewport();
		}
	}
}

void AIKMapHUD::ToggleMap()
{
	if (map_widget_ == nullptr || global_buff_displayer_ == nullptr)
	{
		return;
	}

	if (map_widget_->GetVisibility() == ESlateVisibility::Hidden)
	{
		global_buff_displayer_->SetVisibility(ESlateVisibility::HitTestInvisible);
		map_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		global_buff_displayer_->SetVisibility(ESlateVisibility::Hidden);
		map_widget_->SetVisibility(ESlateVisibility::Hidden);
	}
}