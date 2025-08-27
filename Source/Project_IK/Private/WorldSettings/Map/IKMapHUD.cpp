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
#include "UI/Inventory/InventoryWidget.h"
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
}

void AIKMapHUD::ToggleMap()
{
	if (map_widget_ == nullptr)
	{
		return;
	}

	if (map_widget_->GetVisibility() == ESlateVisibility::Hidden)
	{
		map_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		map_widget_->SetVisibility(ESlateVisibility::Hidden);
	}
}