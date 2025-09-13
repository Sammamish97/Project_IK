/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.15.2025
Summary : Source file for perk HUD Widget

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PerkTrees/PerkHUDWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Managers/TextManager.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "UI/PerkTrees/PerkConnectionWidget.h"
#include "UI/PerkTrees/PerkPopupWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UPerkHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TArray<UUserWidget*> output_;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), output_, UPerkConnectionWidget::StaticClass(), false);
	perk_connections_cache_ = output_;
	perk_popup_widget_->SetVisibility(ESlateVisibility::Hidden);
	
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();

	if (progress_system_cache_ == nullptr)
	{
		progress_system_cache_ = game_instance->GetSubsystem<UPerkProgressSubsystem>();
	}
	visibility_button_->OnClicked.AddDynamic(this, &UPerkHUDWidget::ClosePerkTree);
	SetPerkPointText();
}

void UPerkHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//Animation
	//UpdatePerkTreeConnectionOpacity();
	//UpdatePerkTreeTransform();

	//Update Wheel Zoom
	mouse_wheel_delta_ = UKismetMathLibrary::FInterpTo_Constant(mouse_wheel_delta_,
			0,
			InDeltaTime,
			10.0f);

	float tree_scale_ = perk_tree_widget_->GetRenderTransform().Scale.X;
	tree_scale_ = FMath::Clamp(UKismetMathLibrary::FInterpTo_Constant(tree_scale_,
		   tree_scale_ + mouse_wheel_delta_,
		   InDeltaTime,
		   1.5), 0.4f, 1.5f);
	perk_tree_widget_->SetRenderScale({tree_scale_, tree_scale_});

	//Update panning
	if (is_mouse_down_)
	{
		float pos_x, pos_y;
		UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), pos_x, pos_y);
		FVector2D pos = FVector2D(pos_x, pos_y);
		pos -= mouse_position_;

		FVector2D view_port_size = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
		view_port_size *= 0.5f;

		FVector2D result = FVector2D(FMath::Clamp(pos.X, view_port_size.X * -1.f, view_port_size.X), FMath::Clamp(pos.Y, view_port_size.Y * -1.f, view_port_size.Y));
		UWidgetLayoutLibrary::SlotAsCanvasSlot(perk_tree_widget_)->SetPosition(result);
	}
}

FReply UPerkHUDWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && is_menu_opened_)
	{
		is_mouse_down_ = true;
		float pos_x, pos_y;
		UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), pos_x, pos_y);
		FVector2D pos = FVector2D(pos_x, pos_y);
		mouse_position_ = pos - UWidgetLayoutLibrary::SlotAsCanvasSlot(perk_tree_widget_)->GetPosition();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	}
	return FReply::Handled();
}

FReply UPerkHUDWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	is_mouse_down_ = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	return FReply::Handled();
}

FReply UPerkHUDWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
	mouse_wheel_delta_ = InMouseEvent.GetWheelDelta();
	return FReply::Handled();
}

bool UPerkHUDWidget::IsMenuOpened() const
{
	return is_menu_opened_;
}

void UPerkHUDWidget::ClosePerkTree()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPerkHUDWidget::SetPerkPointText()
{
	FFormatNamedArguments args;
	FText base_text = text_manager_cache_->GetPopUpText("LP");

	args.Add("LP", FText::AsNumber(progress_system_cache_->LoadPerkPoint()));
	perk_point_text_->SetText(FText::Format(base_text, args));
}

float UPerkHUDWidget::ClampPerkConnectionOpacity(float value)
{
	return FMath::Clamp(GetRenderOpacity(), 0, value);
}

void UPerkHUDWidget::SetPopupDetail(const FPerkNodeDetail& node_detail)
{
	perk_popup_widget_->SetPerkData(node_detail);
}
