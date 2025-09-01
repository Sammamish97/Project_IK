/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.15.2025
Summary : Source file for perk popup Widget

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PerkTrees/PerkPopupWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "WorldSettings/IKGameInstance.h"

class UIKGameInstance;

void UPerkPopupWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	// if (IsDesignTime())
	// {
	// 	UpdatePosition();
	// }
}

void UPerkPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
}

void UPerkPopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
	{
		UpdatePosition();
	}
}

void UPerkPopupWidget::UpdatePosition()
{
	float pos_x, pos_y;
	UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), pos_x, pos_y);
	FVector2D pos = FVector2D(pos_x, pos_y);

	FVector2D offset;
	offset.X = FMath::Lerp(offset_x * -1.0, offset_x, GetRenderTransform().Scale.X);
	offset.Y = offset_y;
	
	UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(offset + pos);
}

void UPerkPopupWidget::UpdateSkillDetail()
{
	//Set Cost
	FText cost_text;
	if (perk_data_.purchased_)
	{
		cost_text = text_manager_cache_->GetPopUpText("PURCHASED");
	}
	else
	{
		cost_text = text_manager_cache_->GetPopUpText("PP");
		FFormatNamedArguments args;
		args.Add("PP", FText::AsNumber(perk_data_.cost_));
		
		cost_text = FText::Format(cost_text, args);
	}
	
	cost_text_->SetText(cost_text);
	name_text_->SetText(text_manager_cache_->GetPerkNameText(perk_data_.key_));
	detail_text_->SetText(text_manager_cache_->GetPerkDetailText(perk_data_.key_));
}

void UPerkPopupWidget::SetPerkData(const FPerkNodeDetail& perk_data)
{
	perk_data_ = perk_data;
	if (perk_data_.thumbnail_ == nullptr)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UpdatePosition();
		UpdateSkillDetail();
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
