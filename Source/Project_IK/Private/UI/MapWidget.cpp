/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for displaying maps.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/MapWidget.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Project_IK/Public/WorldSettings/IKGameInstance.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/ScrollBox.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Blueprint/WidgetTree.h"
#include "Rendering/DrawElements.h"

#include "Managers/LevelTransitionManager.h"
#include "Managers/TextureManager.h"

#include "UI/IKMaps.h"

UMapWidget::UMapWidget(const FObjectInitializer& object_initializer)
	: Super::UUserWidget(object_initializer)
{
	root_canvas_panel_ = nullptr;
	maps_ = nullptr;
}

bool UMapWidget::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	// I don't know reason why but it should be in this function.
	InitializeWidgetTree();


	return true;
}

int32 UMapWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// Call the parent implementation first
	int32 CurrentLayer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	// Define the start and end points for the line
	FVector2D StartPoint = FVector2D(0, 0);  // Top-left corner
	FVector2D EndPoint = AllottedGeometry.GetLocalSize();  // Bottom-right corner based on widget size

	// Define color and thickness
	FLinearColor LineColor = FLinearColor::Red * 0.4f;
	float LineThickness = 5.0f;
	
	FSlateClippingZone clipping_zone(scroll_box_->GetPaintSpaceGeometry());
	OutDrawElements.PushClip(clipping_zone);

	for (int32 i = 0; i < maps_->GetHeight(); ++i)
	{
		for (int32 j = 0; j < maps_->GetWidth(); ++j)
		{

			const FMapNode& node = maps_->GetNode(i, j);
			for (int32 k = 0; k < node.next.Num(); k++)
			{
				TArray<FVector2D> line;
				
				TWeakObjectPtr<UButton> departures = buttons_[FIntPoint(i, j)];
				line.Add(GetButtonPosition(departures));
				TWeakObjectPtr<UButton> arrivals = buttons_[FIntPoint(i + 1, node.next[k])];
				line.Add(GetButtonPosition(arrivals));

				if (!departures->GetPaintSpaceGeometry().GetLocalSize().IsNearlyZero() && !arrivals->GetPaintSpaceGeometry().GetLocalSize().IsNearlyZero())
				{
					static constexpr int32 DrawBelowButtons = -34;
					FSlateDrawElement::MakeLines(OutDrawElements, CurrentLayer + DrawBelowButtons, AllottedGeometry.ToPaintGeometry(), line, ESlateDrawEffect::None, LineColor, true, LineThickness);
				}
			}
		}
	}
	OutDrawElements.PopClip();

	return CurrentLayer;
}

void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWidgets();
}

void UMapWidget::NativeDestruct()
{
	for (TPair<FIntPoint,TWeakObjectPtr<UButton>>& button : buttons_)
	{
		button.Value->OnClicked.Clear();
	}
}

void UMapWidget::InitializeWidgetTree()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("MapWidgetRootCanvas"));
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UMapWidget::InitializeButtons()
{
	buttons_.Empty();

	auto ik_game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UTexture2D* enemy_icon_texture = ik_game_instance->GetTextureManager()->GetTexture("enemy_icon");
	if (!enemy_icon_texture)
	{
		return;
	}

	FVector2D button_size(50.f, 50.f);

	if (ik_game_instance)
	{
		maps_ = ik_game_instance->GetMapPtr();

		if (maps_.Get())
		{
			for (int32 i = 0; i < maps_->GetHeight(); i++)
			{
				for (int32 j = 0; j < maps_->GetWidth(); j++)
				{
					const FMapNode& node = maps_->GetNode(i, j);
					
					if (node.type == NodeType::None)
					{
						continue;
					}

					// Init buttons
					UButton* button = NewObject<UButton>();
					FButtonStyle button_style;
					FSlateBrush new_brush;
					new_brush.SetResourceObject(enemy_icon_texture);
					new_brush.DrawAs = ESlateBrushDrawType::Type::Image;
					new_brush.TintColor = FSlateColor(FLinearColor(0.69f, 0.69f, 0.69f));
					new_brush.SetImageSize(FDeprecateSlateVector2D(128.f, 128.f));
					button_style.SetNormal(new_brush);
					new_brush.TintColor = FSlateColor(FLinearColor(0.95f, 0.95f, 0.95f));
					button_style.SetHovered(new_brush);
					new_brush.TintColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));
					button_style.SetPressed(new_brush);
					button->SetStyle(button_style);
					UGridSlot* button_slot = buttons_holder_->AddChildToGrid(button);
					if (button_slot)
					{
						button_slot->SetPadding(FMargin(32.f));
						SetSlotRowCol(button_slot, i, j);
					}

					button->SetIsEnabled(false);

					button->OnClicked.AddDynamic(this, &UMapWidget::OpenLevel);

					buttons_.Add(FIntPoint(i, j), button);
				}
			}

		}
	}

	EnableReachableButtons();

	// Display check icons on visited nodes
	check_images_.Empty();
	const TArray<FIntPoint> visited_nodes = maps_->GetPlayerVisitedPath();
	UTexture2D* check_texture = ik_game_instance->GetTextureManager()->GetTexture("check_icon");
	FSlateBrush check_brush;
	check_brush.SetResourceObject(check_texture);
	check_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	check_brush.SetImageSize(FVector2D(128.0));
	

	for (size_t i = 0; i < visited_nodes.Num(); i++)
	{
		UImage* check = NewObject<UImage>();
		check->SetBrush(check_brush);
		UGridSlot* check_slot = buttons_holder_->AddChildToGrid(check);
		if (check_slot)
		{
			check_slot->SetPadding(FMargin(16.f));
			SetSlotRowCol(check_slot, visited_nodes[i].X, visited_nodes[i].Y);
			static constexpr int32 DrawAboveButton = 1;
			check_slot->SetLayer(DrawAboveButton);
		}

		TWeakObjectPtr<UButton> visited_button = buttons_[visited_nodes[i]];
		FButtonStyle visited_style = visited_button->GetStyle();
		visited_style.SetDisabled(visited_style.Normal);
		visited_button->SetStyle(visited_style);
	}
}

void UMapWidget::InitializeWidgets()
{
	background_border_ = NewObject<UBorder>();
	background_border_->Rename(*MakeUniqueObjectName(GetOuter(), background_border_->GetClass(), TEXT("Background")).ToString());
	background_border_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	background_border_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* background_border_slot = root_canvas_panel_->AddChildToCanvas(background_border_.Get());
	background_border_slot->SetAnchors(FAnchors(0.5f, 0.5f));
	background_border_slot->SetPosition(FVector2D(-800.0, -400.0));
	background_border_slot->SetSize(FVector2D(1600.0, 800.0));

	scroll_box_ = NewObject<UScrollBox>();
	scroll_box_->Rename(*MakeUniqueObjectName(GetOuter(), scroll_box_->GetClass(), TEXT("ScrollBox")).ToString());
	UBorderSlot* scroll_box_slot = Cast<UBorderSlot>(background_border_->AddChild(scroll_box_.Get()));
	scroll_box_slot->SetPadding(FMargin(0.f, 32.f));
	scroll_box_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	scroll_box_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

	buttons_holder_ = NewObject<UGridPanel>();
	buttons_holder_->Rename(*MakeUniqueObjectName(GetOuter(), scroll_box_->GetClass(), TEXT("Buttons Holder")).ToString());
	scroll_box_->AddChild(buttons_holder_.Get());

	InitializeButtons();
}

FVector2D UMapWidget::GetButtonPosition(TWeakObjectPtr<UButton> button) const
{
	return background_border_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f)) + scroll_box_->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f)) + button->GetPaintSpaceGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0)) - FVector2D(0.0, scroll_box_->GetScrollOffset()) + (button->GetPaintSpaceGeometry().GetLocalSize() / 2.f);
}

void UMapWidget::EnableReachableButtons()
{
	FIntPoint player_grid_position = maps_->GetPlayerGridPosition();
	if (player_grid_position.X < 0 && player_grid_position.Y < 0)
	{
		// If we are in hero select level, (nothing progress recorded)
		EnableZeroLevelButtons();
		return;
	}
	FMapNode node = maps_->GetNode(player_grid_position.X, player_grid_position.Y);
	for (int32 i = 0; i < node.next.Num(); i++)
	{
		buttons_[FIntPoint(player_grid_position.X + 1, node.next[i])]->SetIsEnabled(true);
	}
	// Update scroll bar
	scroll_box_->ScrollWidgetIntoView(buttons_[player_grid_position].Get());
}

void UMapWidget::EnableZeroLevelButtons()
{
	int32 final_column = -1;
	for (int32 i = 0; i < maps_->GetWidth(); i++)
	{
		if (maps_->GetNode(0, i).type != NodeType::None)
		{
			buttons_[FIntPoint(0, i)]->SetIsEnabled(true);
			final_column = i;
		}
	}
	// Update scroll bar
	scroll_box_->ScrollWidgetIntoView(buttons_[FIntPoint(0, final_column)].Get());
	return;
}

void UMapWidget::SetSlotRowCol(UGridSlot* GridSlot, int32 Row, int32 Column)
{
	GridSlot->SetRow(maps_->GetHeight() - 1 - Row);
	GridSlot->SetColumn(Column);
}

void UMapWidget::OpenLevel()
{
	UWorld* world = GetWorld();

	for (const TPair<FIntPoint, TWeakObjectPtr<UButton>>& pair : buttons_)
	{
		if (pair.Value->IsHovered())
		{
			Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world))->GetLevelTransitionManager()->OpenLevel(world, pair.Key);
		}
	}

}
