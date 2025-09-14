/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Source file for perk connection widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PerkTrees/PerkConnectionWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/PerkTrees/PerkNodeWidget.h"

void UPerkConnectionWidget::InitConnection(UPerkNodeWidget* owner, FVector2D end_point,
	FPerkConnectionColor connection_color)
{
	owner_perk_node_ = owner;
	connection_end_point_ = end_point;
	connection_color_ = connection_color;
}

void UPerkConnectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (owner_perk_node_)
	{
		if (owner_perk_node_->IsPurchased())
		{
			current_purchase_connection_ = connection_end_point_;
		}
	}
}

void UPerkConnectionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (owner_perk_node_)
	{
		if (owner_perk_node_->IsPurchased())
		{
			if (UKismetMathLibrary::Distance2D(current_purchase_connection_, connection_end_point_) >= 5.f)
			{
				current_purchase_connection_ = UKismetMathLibrary::Vector2DInterpTo_Constant(current_purchase_connection_, purchase_connection_target_, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 275.f);
			}
		}
		else
		{
			UpdateConnections(1.0);
		}
	}
}

int32 UPerkConnectionWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FPaintContext context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	UWidgetBlueprintLibrary::DrawLine(context, FVector2D::Zero(), connection_end_point_, connection_color_.default_color_, true, 10.f);
	UWidgetBlueprintLibrary::DrawLine(context, FVector2D::Zero(), current_purchase_connection_, connection_color_.purchased_, true, 11.f);

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
							  bParentEnabled);
}

bool UPerkConnectionWidget::UpdateConnections(float duration)
{
	current_purchase_connection_ = Vector2DLerp(duration);
	float begin_to_mid = UKismetMathLibrary::Distance2D(current_purchase_connection_, FVector2D::Zero());
	float mid_to_end = UKismetMathLibrary::Distance2D(current_purchase_connection_, purchase_connection_target_);
	return begin_to_mid > 20.f && mid_to_end < 20.f;
}

void UPerkConnectionWidget::SetLineConnectionTarget(bool purchase)
{
	if (purchase)
	{
		purchase_connection_target_ = connection_end_point_;
	}
	else
	{
		purchase_connection_target_ = FVector2D::Zero();
	}
}

FVector2D UPerkConnectionWidget::Vector2DLerp(float duration)
{
	FVector2D result;
	timer_ = UKismetMathLibrary::FInterpTo_Constant(timer_,
		UKismetMathLibrary::SelectFloat(0.f,
			duration,
			UKismetMathLibrary::EqualEqual_Vector2DVector2D(purchase_connection_target_, FVector2D(0, 0))),
			 UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 1.f);

	if (timer_ != duration)
	{
		float alpha = timer_ / duration;
		result = {FMath::Lerp(0, connection_end_point_.X, alpha), FMath::Lerp(0, connection_end_point_.Y, alpha) };
	}
	return result;
}
