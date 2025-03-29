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

void AIKMapHUD::BeginPlay()
{
	Super::BeginPlay();
	if(inventory_widget_class_)
	{
		inventory_widget_ = CreateWidget<UInventoryWidget>(GetWorld(), inventory_widget_class_);
		if(inventory_widget_)
		{
			auto instance = UGameplayStatics::GetGameInstance(GetWorld());
			auto ik_instance = Cast<UIKGameInstance>(instance);
			if(ik_instance)
			{
				inventory_widget_->InitInventoryWidget(ik_instance->GetInventoryManager());
				inventory_widget_->AddToViewport();
				inventory_widget_->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}

	if (map_widget_class_)
	{
		map_widget_ = CreateWidget<UUserWidget>(GetWorld(), map_widget_class_);
		if (map_widget_)
		{
			map_widget_->AddToViewport();
		}
	}
}

void AIKMapHUD::PopUpInventory()
{
	inventory_widget_->AddToViewport();
	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->bShowMouseCursor = true;
}

void AIKMapHUD::RemoveInventory()
{
	inventory_widget_->RemoveFromParent();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}