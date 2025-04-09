/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.25.2024
Summary : Source file for UI to pick an item.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ItemPickerUI.h"

#include "Managers/EnumCluster.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CheckBox.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Abilities/ItemInventory.h"
#include "WorldSettings/IKHUD.h"
#include "Managers/CombatLevelResultManager.h"
#include "Structs/ItemData.h"
#include "Managers/TextureManager.h"


bool UItemPickerUI::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return success;
	}

	InitializeRootWidget();

	return true;
}

void UItemPickerUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FadeInOutHighlight(InDeltaTime);
}

void UItemPickerUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeChildWidgets();
	
	selected_button_index_ = -1;
	highlight_current_opacity_ = 0.f;
	highlight_fade_speed_ = 2.f;
	is_highligh_fade_in_ = true;
}

void UItemPickerUI::NativeDestruct()
{
	for (UButton* button : buttons_)
	{
		button->OnClicked.Clear();
	}
	if (skip_checkbox_->OnCheckStateChanged.IsBound())
	{
		skip_checkbox_->OnCheckStateChanged.Clear();
	}

	select_button_->OnClicked.Clear();

	buttons_.Empty();
}

void UItemPickerUI::InitializeRootWidget()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>();
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UItemPickerUI::InitializeChildWidgets()
{
	background_ = NewObject<UBorder>();
	background_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	background_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* background_slot = root_canvas_panel_->AddChildToCanvas(background_.Get());
	if (background_slot)
	{
		background_slot->SetAnchors(FAnchors(0.5f, 0.5f));
		background_slot->SetSize(FVector2D(900.0, 800.0));
		background_slot->SetPosition(FVector2D(-450.0, -400.0));
	}

	widgets_holder_ = NewObject<UVerticalBox>();
	UBorderSlot* widgets_holder_slot = Cast<UBorderSlot>(background_->AddChild(widgets_holder_.Get()));
	if (widgets_holder_slot)
	{
		widgets_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		widgets_holder_slot->SetPadding(FMargin());
	}

	title_ = NewObject<UTextBlock>();
	title_->SetText(FText::FromString("Take one of items"));
	FSlateFontInfo magnified_font = title_->GetFont();
	magnified_font.Size = 48;
	title_->SetFont(magnified_font);
	UVerticalBoxSlot* title_slot = widgets_holder_->AddChildToVerticalBox(title_.Get());
	if (title_slot)
	{
		title_slot->SetPadding(FMargin(0.f, 32.f));
		title_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		title_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	description_ = NewObject<UTextBlock>();
	description_->SetText(FText::FromString("Descriptions of a selected item will be shown here.\nPick up one of them."));
	description_->SetAutoWrapText(true);
	UVerticalBoxSlot* description_slot = widgets_holder_->AddChildToVerticalBox(description_.Get());
	if (description_slot)
	{
		description_slot->SetPadding(FMargin(32.0, 0.0));
		description_slot->SetSize(FSlateChildSize(ESlateSizeRule::Type::Fill));
	}

	buttons_holder_ = NewObject<UHorizontalBox>();
	UVerticalBoxSlot* buttons_holder_slot = widgets_holder_->AddChildToVerticalBox(buttons_holder_.Get());
	if (buttons_holder_slot)
	{
		buttons_holder_slot->SetSize(FSlateChildSize(ESlateSizeRule::Type::Fill));
		buttons_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		buttons_holder_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!game_instance)
	{
		return;
	}

	item_candidates_ = game_instance->GetDataTableManager()->GetUniqueItemDataRandomly(3);

	for (int32 i = 0; i < 3; i++)
	{	
		TWeakObjectPtr<UButton> button = NewObject<UButton>();
		FButtonStyle button_style;
		FSlateBrush new_brush;
		new_brush.SetResourceObject(item_candidates_[i].item_icon_);
		new_brush.DrawAs = ESlateBrushDrawType::Type::Image;
		new_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
		new_brush.SetImageSize(FVector2D(128.0, 128.0));
		button_style.SetNormal(new_brush);
		new_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
		button_style.SetHovered(new_brush);
		new_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
		button_style.SetPressed(new_brush);
		button->SetStyle(button_style);
		button->OnClicked.AddDynamic(this, & UItemPickerUI::ItemButtonOnClicked);
		UHorizontalBoxSlot* button_slot = buttons_holder_->AddChildToHorizontalBox(button.Get());

		if (button_slot)
		{
			button_slot->SetPadding(FMargin(64.0, 0.0));
		}
		buttons_.Add(button.Get());
	}

	skip_holder_ = NewObject<UVerticalBox>();
	UVerticalBoxSlot* skip_holder_slot = widgets_holder_->AddChildToVerticalBox(skip_holder_);
	if (skip_holder_slot)
	{
		skip_holder_slot->SetPadding(FMargin(0.f, 0.f, 0.f, 32.f));
		skip_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		skip_holder_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	skip_checkbox_ = NewObject<UCheckBox>();
	skip_checkbox_->HorizontalAlignment = EHorizontalAlignment::HAlign_Center;
	skip_checkbox_->OnCheckStateChanged.AddDynamic(this, &UItemPickerUI::OnSkipCheckedStateChanged);
	UVerticalBoxSlot* skip_checkbox_slot = skip_holder_->AddChildToVerticalBox(skip_checkbox_);
	if (skip_checkbox_slot)
	{
		skip_checkbox_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		skip_checkbox_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
	
	skip_text_ = NewObject<UTextBlock>();
	skip_text_->SetText(FText::FromString("Ignore them."));
	skip_text_->SetColorAndOpacity(FLinearColor(0.65f, 0.65f, 0.65f));
	FSlateFontInfo skip_text_font_info = skip_text_->GetFont();
	skip_text_font_info.Size = 16;
	skip_text_->SetFont(skip_text_font_info);
	UVerticalBoxSlot* skip_text_slot = skip_holder_->AddChildToVerticalBox(skip_text_);
	if (skip_text_slot)
	{
		skip_text_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		skip_text_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	UTexture2D* select_texture = game_instance->GetTextureManager()->GetTexture("take_it_button");
	select_button_ = NewObject<UButton>();
	FButtonStyle button_style;
	FSlateBrush select_brush;
	select_brush.SetResourceObject(select_texture);
	select_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	select_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
	select_brush.SetImageSize(FVector2D(256.0, 64.0));
	button_style.SetNormal(select_brush);
	select_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
	button_style.SetHovered(select_brush);
	select_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
	button_style.SetPressed(select_brush);
	select_button_->SetStyle(button_style);
	select_button_->OnClicked.AddDynamic(this, &UItemPickerUI::SelectButtonBindingFunc);
	select_button_->SetIsEnabled(false);
	UVerticalBoxSlot* select_button_slot = widgets_holder_->AddChildToVerticalBox(select_button_.Get());
	if (select_button_slot)
	{
		select_button_slot->SetPadding(FMargin(0.0, 0.0, 0.0, 32.0));
		select_button_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		select_button_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	UTexture2D* highlight_texture = game_instance->GetTextureManager()->GetTexture("highlight_image");
	highlight_image_ = NewObject<UImage>();
	FSlateBrush highlight_brush;
	highlight_brush.SetResourceObject(highlight_texture);
	highlight_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	highlight_brush.SetImageSize(FVector2D(128.0, 128.0));
	highlight_image_->SetBrush(highlight_brush);
	UCanvasPanelSlot* highlight_image_slot = root_canvas_panel_->AddChildToCanvas(highlight_image_.Get());
	// @@ TODO: Fixed size data is may not appropriate for the all environments.
	highlight_image_slot->SetSize(FVector2D(125.0));
	highlight_image_->SetVisibility(ESlateVisibility::Hidden);
}

void UItemPickerUI::FadeInOutHighlight(float InDeltaTime)
{
	if (selected_button_index_ >= 0)
	{
		if (is_highligh_fade_in_)
		{	// Fade In
			highlight_current_opacity_ += InDeltaTime * highlight_fade_speed_;
			if (highlight_current_opacity_ >= 1.f)
			{
				highlight_current_opacity_ = 1.f;
				is_highligh_fade_in_ = false;
			}
		}
		else
		{	// Fade Out
			highlight_current_opacity_ -= InDeltaTime * highlight_fade_speed_;
			if (highlight_current_opacity_ <= 0.f)
			{
				highlight_current_opacity_ = 0.f;
				is_highligh_fade_in_ = true;
			}
		}

		highlight_image_->SetRenderOpacity(highlight_current_opacity_);
	}
}

void UItemPickerUI::SelectButtonBindingFunc()
{
	// Add selected item to inventory
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (game_instance)
	{
		if (skip_checkbox_->IsChecked())
		{
			GoToNextStep();
		}
		else if (selected_button_index_ >= 0 && selected_button_index_ < item_candidates_.Num())
		{
			game_instance->GetItemInventory()->AddItem(item_candidates_[selected_button_index_], [this]() 
				{
					GoToNextStep();
				}
			);
		}
	}
}

void UItemPickerUI::ItemButtonOnClicked()
{
	for (int32 i = 0; i < buttons_.Num(); i++)
	{
		if (buttons_[i]->IsHovered())
		{
			// Enable selection button when an item selected
			if (selected_button_index_ < 0)
			{
				select_button_->SetIsEnabled(true);
			}
			selected_button_index_ = i;


			UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(highlight_image_->Slot);
			slot->SetPosition(GetButtonPosition(selected_button_index_));
			if (highlight_image_->GetVisibility() == ESlateVisibility::Hidden)
			{
				highlight_image_->SetVisibility(ESlateVisibility::Visible);
			}
			description_->SetText(FText::FromString(item_candidates_[selected_button_index_].item_description_));
		}
	}
}

FVector2D UItemPickerUI::GetButtonPosition(int32 ButtonIndex) const
{
	// Border -> VerticalBox -> HorizontalBox -> Button
	return background_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) + widgets_holder_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) + buttons_holder_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) + buttons_[ButtonIndex]->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0));
}

void UItemPickerUI::OnSkipCheckedStateChanged(bool bIsChecked)
{
	selected_button_index_ = -1;
	highlight_image_->SetVisibility(ESlateVisibility::Hidden);

	if (bIsChecked)
	{
		select_button_->SetIsEnabled(true);
	}
	else
	{
		select_button_->SetIsEnabled(false);
	}
}

void UItemPickerUI::GoToNextStep() const
{
	// Update HUD status
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		hud->SynchroItemButtons();
		hud->SwitchUIByState(ELevelEndState::ShowingMapUI);
	}
}
