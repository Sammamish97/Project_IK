/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.21.2025
Summary : Source file for UI to check confirmation.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ConfirmationWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UConfirmationWidget::SetText(FText text)
{
	text_->SetText(text);
}

void UConfirmationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Use manual SetWrapTextAt instead of Enabling AutoWrapText to prevent wrapping glitches
	UCanvasPanelSlot* border_slot = Cast<UCanvasPanelSlot>(border_->Slot);
	if (border_slot)
	{
		UVerticalBoxSlot* text_slot = Cast<UVerticalBoxSlot>(text_->Slot);
		if (text_slot)
		{
			text_->SetWrapTextAt(border_slot->GetSize().X - text_slot->GetPadding().Right);
		}
	}

	button_->OnClicked.AddDynamic(this, &UConfirmationWidget::OnButtonClicked);
}

void UConfirmationWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (button_->OnClicked.IsBound())
	{
		button_->OnClicked.Clear();
	}
	if (OnConfirmation.IsBound())
	{
		OnConfirmation.Clear();
	}
}

FReply UConfirmationWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// If click is outside the confirmation button, consider it a denial.
	RemoveFromParent();

	return FReply::Handled();
}

void UConfirmationWidget::OnButtonClicked()
{
	OnConfirmation.Broadcast();
	RemoveFromParent();
}
