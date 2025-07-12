/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for UI that displays buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/BuffDisplayer.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UBuffDisplayer::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	InitializeRootWidget();

	return true;
}

void UBuffDisplayer::SetImage(UTexture2D* Texture)
{
	if (dynamic_material_)
	{
		dynamic_material_->SetTextureParameterValue(TEXT("texture"), Texture);
	}
}

void UBuffDisplayer::SetBackground(FLinearColor color)
{
	if (dynamic_material_)
	{
		dynamic_material_->SetVectorParameterValue(TEXT("background"), color);
	}
}

void UBuffDisplayer::SetDuplicatedText(int32 Duplicated)
{
	if (duplicated_text_->GetVisibility() != ESlateVisibility::Visible)
	{
		duplicated_text_->SetVisibility(ESlateVisibility::Visible);
	}

	duplicated_text_->SetText(FText::Format(NSLOCTEXT("UI", "BuffDisplayerDuplicated", "x{0}"), Duplicated));
}

void UBuffDisplayer::HideText() const
{
	duplicated_text_->SetVisibility(ESlateVisibility::Hidden);
}

void UBuffDisplayer::NativeConstruct()
{
	InitializeChildWidgets();
}

void UBuffDisplayer::InitializeRootWidget()
{
	root_widget_ = WidgetTree->ConstructWidget<UOverlay>();
	WidgetTree->RootWidget = root_widget_.Get();
}

void UBuffDisplayer::InitializeChildWidgets()
{
	buff_image_ = WidgetTree->ConstructWidget<UImage>();
	if (image_material_)
	{
		dynamic_material_ = UMaterialInstanceDynamic::Create(image_material_, this);
		if (dynamic_material_)
		{
			buff_image_->SetBrushFromMaterial(dynamic_material_);
		}
	}
	root_widget_->AddChild(buff_image_.Get());

	duplicated_text_ = WidgetTree->ConstructWidget<UTextBlock>();
	duplicated_text_->SetText(FText::FromString("xN"));
	FSlateFontInfo font = duplicated_text_->GetFont();
	font.Size = 16.f;
	font.OutlineSettings.OutlineSize = 1;
	duplicated_text_->SetFont(font);
	duplicated_text_->SetVisibility(ESlateVisibility::Hidden);
	UOverlaySlot* text_slot = root_widget_->AddChildToOverlay(duplicated_text_.Get());
	if (text_slot)
	{
		text_slot->SetPadding(FMargin(0.f, -8.f, -4.f, 0.f));
		text_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);	
	}
}
