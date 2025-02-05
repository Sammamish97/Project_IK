/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for UI to unlock heros' perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/PerkUnlockWidget.h"

#include "Blueprint/WidgetTree.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"



void UPerkUnlockWidget::NativeConstruct()
{
	UProgressBar* progress_bar = WidgetTree->ConstructWidget<UProgressBar>();
	// @@ TODO: Calculate angle between nodes
	progress_bar->SetRenderTransformAngle(90.f);
	progress_bar->SetRenderTransformPivot(FVector2D(0.0, 0.5));
	// @@ TODO: Set percent.
	progress_bar->SetPercent(0.f);
	UCanvasPanelSlot* progress_slot = scroll_panel_->AddChildToCanvas(progress_bar);
	if (progress_slot)
	{
		// Top-center anchor
		progress_slot->SetAnchors(FAnchors(0.5f, 0.f));
		progress_slot->SetSize(FVector2D(300.f, 15.f));
		progress_slot->SetPosition(FVector2D(0.f));
	}


	UVerticalBox* vertical_box = WidgetTree->ConstructWidget<UVerticalBox>();
	UCanvasPanelSlot* vertical_slot = scroll_panel_->AddChildToCanvas(vertical_box);
	if (vertical_slot)
	{
		// Full stretch anchor
		vertical_slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		vertical_slot->SetOffsets(FMargin(0.f));
		vertical_slot->SetAutoSize(true);
	}

	UHorizontalBox* level_0_box = WidgetTree->ConstructWidget<UHorizontalBox>();
	UVerticalBoxSlot* level_0_box_slot = vertical_box->AddChildToVerticalBox(level_0_box);
	if (level_0_box_slot)
	{
		level_0_box_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		level_0_box_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	UButton* node0 = WidgetTree->ConstructWidget<UButton>();
	FButtonStyle style;
	FSlateBrush normal_brush;
	normal_brush.SetImageSize(FVector2D(128.f, 128.f));
	normal_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	normal_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
	style.SetNormal(normal_brush);
	FSlateBrush hovered_brush = normal_brush;
	hovered_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
	style.SetHovered(hovered_brush);
	FSlateBrush pressed_brush = normal_brush;
	pressed_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
	style.SetPressed(pressed_brush);
	node0->SetStyle(style);
	UHorizontalBoxSlot* node0_slot = level_0_box->AddChildToHorizontalBox(node0);
	if (node0_slot)
	{
		node0_slot->SetPadding(FMargin(64.f));
	}
}

void UPerkUnlockWidget::NativeDestruct()
{
}
