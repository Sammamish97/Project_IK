/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Source file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MiniRuneBoardWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ProgressBar.h"
#include "Components/RuneMechanics.h"
#include "Components/SizeBox.h"
#include "UI/RuneBoardEdgeWidget.h"
#include "UI/MiniRuneSlotWidget.h"
#include "UI/RunePopupWidget.h"
void UMiniRuneBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	float r = 30;

	auto vertices = ComputeVertices(r);
	auto edges = ComputeEdges(vertices);

	for(int32 i = 0; i < 6; ++i)
	{
		//Left -> Top -> Right -> Bottom
		FMargin margin = {vertices[i].X, 0, 0,  vertices[i].Y};
		UOverlaySlot* rune_slot = CastChecked<UOverlaySlot>(rune_overlay_->GetSlots()[i]);
		rune_slot->SetPadding(margin);
	}
	
	TArray line_array = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};
	TArray<UOverlaySlot*> line_slots;
	for(int32 i = 0; i < 12; ++i)
	{
		 line_slots.Push(CastChecked<UOverlaySlot>(line_overlay_->GetSlots()[i]));
	}
	float temp_height = 2.f;

	TArray idx_map = {0, 4, 7, 9, 11, 3, 1, 8, 2, 5, 10, 6};
	for(int32 i = 0; i < 12; ++i)
	{
		line_slots[i]->SetPadding({edges[idx_map[i]].mid_point.X, 0, 0, edges[idx_map[i]].mid_point.Y});
		line_array[i]->size_box_->SetRenderTransformAngle(FMath::RadiansToDegrees(edges[idx_map[i]].angle));
		line_array[i]->size_box_->SetWidthOverride(edges[idx_map[i]].length);
		line_array[i]->size_box_->SetHeightOverride(temp_height);
	}
}

void UMiniRuneBoardWidget::InitMiniRuneBoard(URuneMechanics* rune_mechanics, URunePopupWidget* rune_popup_widget, EHeroType hero_type)
{
	hero_type_ = hero_type;
	rune_popup_widget_cache_ = rune_popup_widget;

	TArray line_array = {line_0_, line_1_, line_2_, line_3_, line_4_, line_5_, line_6_, line_7_, line_8_, line_9_, line_10_, line_11_};
    TArray rune_widget_array = {rune_0_, rune_1_, rune_2_, rune_3_, rune_4_, rune_5_};
    auto rune_data_array = rune_mechanics->GetEquippedRunes();

    for(int32 i = 0; i < 6; ++i)
    {
    	if(rune_data_array[i].set_type != ERuneSetType::INVALID)
    	{
    		rune_widget_array[i]->image_->SetColorAndOpacity(FLinearColor::Red);	
    	}
    	else
    	{
    		rune_widget_array[i]->image_->SetVisibility(ESlateVisibility::Hidden);
    	}
    }

	for(int32 i = 0; i < 12; ++i)
	{
		line_array[i]->progress_bar_->SetVisibility(ESlateVisibility::Hidden);
	}

    auto result = rune_mechanics->GetSetBonusData();
    for (const auto& elem : result)
    {
    	if (elem.Value.Num() == 2)
    	{
    		line_array[elem.Value[0]]->progress_bar_->SetVisibility(ESlateVisibility::Visible);
    	}
    	else if (elem.Value.Num() == 3)
    	{
    		line_array[6 + 3 * elem.Value[0]]->progress_bar_->SetVisibility(ESlateVisibility::Visible);
    		line_array[7 + 3 * elem.Value[0]]->progress_bar_->SetVisibility(ESlateVisibility::Visible);
    		line_array[8 + 3 * elem.Value[0]]->progress_bar_->SetVisibility(ESlateVisibility::Visible);
    	}
    	else if (elem.Value.Num() == 6)
    	{
    		for (int i = 0; i < 6; ++i)
    		{
    			line_array[i]->progress_bar_->SetVisibility(ESlateVisibility::Visible);
    		}
    	}
    }
}

void UMiniRuneBoardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	rune_popup_widget_cache_->UpdateRuneData(hero_type_);
}

void UMiniRuneBoardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	rune_popup_widget_cache_->ResetWidget();
}

TArray<FVector2D> UMiniRuneBoardWidget::ComputeVertices(float radius)
{
	TArray<FVector2D> result;
	for (int32 i = 0; i < 6; ++i) {
		float angle = 2 * PI * i / 6;
		result.Push({radius * FMath::Sin(angle), radius * FMath::Cos(angle)});
	}
	return result;
}

TArray<UMiniRuneBoardWidget::Edge> UMiniRuneBoardWidget::ComputeEdges(const TArray<FVector2D>& vertices)
{
	TArray<Edge> result;
	for (int32 i = 0; i < 6; ++i) {
		for (int32 j = i + 1; j < 6; ++j) {
			// Skip same vertex and opposite vertex
			if (j == (i + 3) % 6) continue;

			FVector2D p1 = vertices[i];
			FVector2D p2 = vertices[j];

			// Midpoint
			FVector2D mid = { (p1.X + p2.X) / 2.0f, (p1.Y + p2.Y) / 2.0f };

			// Length
			float dx = p2.X - p1.X;
			float dy = p2.Y - p1.Y;
			float len = FMath::Sqrt(dx * dx + dy * dy);

			// Angle (radians)
			float angle = FMath::Atan2(dy, dx);
			angle *= -1;

			result.Push({ mid, len, angle });
		}
	}
	return result;
}
