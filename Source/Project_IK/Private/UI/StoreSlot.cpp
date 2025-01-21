/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.17.2024
Summary : Source file for a slot UserWidget for Store.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/StoreSlot.h"

#include "UI/CheckboxButtonWidget.h"
#include "Components/TextBlock.h"

void UStoreSlot::SetTexture(UTexture2D* texture)
{
	checkbox_button_->SetButtonTexture(texture);
}

void UStoreSlot::SetPrice(int32 price)
{
	price_ = price;
	price_text_->SetText(FText::FromString(FString::FromInt(price)));
}

int32 UStoreSlot::GetPrice() const
{
	return price_;
}

bool UStoreSlot::IsChecked() const
{
	return checkbox_button_->IsChecked();
}

void UStoreSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (checkbox_button_)
	{
		checkbox_button_->OnCheckboxButtonClickedDelegate.AddDynamic(this, &UStoreSlot::ForwardButtonClick);
	}
}

void UStoreSlot::NativeDestruct()
{
	Super::NativeDestruct();

	OnStoreSlotClickedDelegate.Clear();
}

void UStoreSlot::ForwardButtonClick()
{
	if (OnStoreSlotClickedDelegate.IsBound())
	{
		OnStoreSlotClickedDelegate.Broadcast();
	}
}
