/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Source file for Skill Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/BasicPopupWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UBasicPopupWidget::UpdatePopupData(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(thumbnail);
	name_->SetText(name);
	detail_->SetText(detail);
}

void UBasicPopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	thumbnail_->SetBrushFromTexture(nullptr);
}

void UBasicPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	SetRenderOpacity(0.f);
	MoveToInsideOfViewport();
}

void UBasicPopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (do_not_draw_single_frame_ == true)
	{
		do_not_draw_single_frame_ = false;
	}
	else
	{
		SetRenderOpacity(1.f);
	}
	MoveToInsideOfViewport();
}

void UBasicPopupWidget::MoveToInsideOfViewport()
{
	// 1) 같은 좌표계로 통일 (DPI 반영된 뷰포트 픽셀)
	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	const float ViewportScale    = UWidgetLayoutLibrary::GetViewportScale(this);

	double mx, my;
	if (!UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), mx, my)) return;
	const FVector2D MousePosDPI(mx, my);

	// 2) 위젯 실제 픽셀 크기
	const FVector2D WidgetSizeDPI = GetDesiredSize() * ViewportScale;

	// 3) 피벗 고정(예: 좌상단 0,0) — 뒤집지 않음
	const FVector2D Pivot(0.f, 0.f);

	// 4) 마우스 기준 목표 위치(좌상단 기준)
	FVector2D TargetTopLeft = MousePosDPI + FollowOffset;

	// 5) 화면 안으로 클램프(“벽에 부딪히면 더 안 나감”)
	const float MinX = ScreenPadding;
	const float MinY = ScreenPadding;
	const float MaxX = ViewportSize.X - ScreenPadding - WidgetSizeDPI.X;
	const float MaxY = ViewportSize.Y - ScreenPadding - WidgetSizeDPI.Y;

	TargetTopLeft.X = UKismetMathLibrary::Clamp(TargetTopLeft.X, MinX, MaxX);
	TargetTopLeft.Y = UKismetMathLibrary::Clamp(TargetTopLeft.Y, MinY, MaxY);

	// 6) 적용 (넘기는 좌표가 DPI 적용 좌표이므로 bRemoveDPIScale=false)
	SetAlignmentInViewport(Pivot);
	SetPositionInViewport(TargetTopLeft, /*bRemoveDPIScale*/ false);
}
