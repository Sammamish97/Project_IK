/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for HUD using PerkUnlockLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/PerkUnlockLevel/IKPerkUnlockHUD.h"

#include "Blueprint/WidgetTree.h"
#include "UI/PerkUnlockWidget.h"

void AIKPerkUnlockHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (perk_unlock_widget_class_)
	{
		perk_unlock_widget_ = CreateWidget<UUserWidget>(world, perk_unlock_widget_class_);
		if (perk_unlock_widget_)
		{
			perk_unlock_widget_->AddToViewport();
		}
	}
}
