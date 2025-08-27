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
#include "UI/PerkTrees/PerkHUDWidget.h"

void AIKPerkUnlockHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (perk_unlock_widget_class_)
	{
		perk_hud_widget_ = CreateWidget<UPerkHUDWidget>(world, perk_unlock_widget_class_);
		if (perk_hud_widget_)
		{
			perk_hud_widget_->AddToViewport();
		}
	}
}

TObjectPtr<UPerkHUDWidget> AIKPerkUnlockHUD::GetPerkHUDWidget()
{
	return perk_hud_widget_;
}
