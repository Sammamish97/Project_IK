/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Source file for HUD that used in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/StoreLevel/IKStoreHUD.h"

#include "UI/StoreWidget.h"

void AIKStoreHUD::BeginPlay()
{
	Super::BeginPlay();

	if (store_widget_class_)
	{
		store_widget_ = CreateWidget<UStoreWidget>(GetWorld(), store_widget_class_);
		if (store_widget_)
		{
			store_widget_->AddToViewport();
		}
	}
}
