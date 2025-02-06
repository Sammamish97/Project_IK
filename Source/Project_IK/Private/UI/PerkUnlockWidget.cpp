/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for UI to unlock heros' perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/PerkUnlockWidget.h"

#include "Blueprint/WidgetTree.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"

#include "Structs/PerkTree.h"


void UPerkUnlockWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConstructPerkTree();
	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UPerkUnlockWidget::ConstructLinks);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPerkUnlockWidget::ConstructLinks, 0.1f, false);
	//ConstructLinks();
}

void UPerkUnlockWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPerkUnlockWidget::ConstructPerkTree()
{
	UPerkTree* perk_tree = UPerkTree::Get();
	TArray<FPerkNode> tree = perk_tree->GetTree();

	// Initialize button array with nullptr
	buttons_.Init(nullptr, tree.Num());

	UVerticalBox* tree_box = ConstructNewTreeBox();

	// node on 0 index in tree is root node of the tree
	TArray<FPerkNode> current_level_nodes({ tree[0]});
	TArray<TObjectPtr<UButton>*> pointer_to_content_of_button_array({ &buttons_[0]});
	while (!current_level_nodes.IsEmpty())
	{
		UHorizontalBox* tree_level = ConstructNewTreeLevel(tree_box);

		// Temporary data
		TArray<FPerkNode> next_level_nodes;
		TArray<TObjectPtr<UButton>*> next_pointers;

		for (int32 i = 0; i < current_level_nodes.Num(); i++)
		{
			// Save created node to array
			UButton* button = ConstructNewTreeNode(tree_level);
			// @@ TODO: Customize button by current node
			*pointer_to_content_of_button_array[i] = button;

			for (int32 next_index = 0; next_index < current_level_nodes[i].next_.Num(); next_index++)
			{
				next_level_nodes.Add(tree[current_level_nodes[i].next_[next_index]]);
				next_pointers.Add(&buttons_[current_level_nodes[i].next_[next_index]]);
			}
		}

		current_level_nodes = MoveTemp(next_level_nodes);
		pointer_to_content_of_button_array = MoveTemp(next_pointers);
	}
}

void UPerkUnlockWidget::ConstructLinks()
{
	TArray<FPerkNode> tree = UPerkTree::Get()->GetTree();

	for (int32 i = 0; i < tree.Num(); i++)
	{
		for (int32 j = 0; j < tree[i].next_.Num(); j++)
		{
			ConstructLink(buttons_[i], buttons_[tree[i].next_[j]]);
		}
	}
}

UVerticalBox* UPerkUnlockWidget::ConstructNewTreeBox()
{
	UVerticalBox* tree_box = WidgetTree->ConstructWidget<UVerticalBox>();
	UCanvasPanelSlot* tree_box_slot = scroll_panel_->AddChildToCanvas(tree_box);
	if (tree_box_slot)
	{
		// Full stretch anchor
		tree_box_slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		tree_box_slot->SetOffsets(FMargin(0.f));
		tree_box_slot->SetAutoSize(true);
	}
	return tree_box;
}

UHorizontalBox* UPerkUnlockWidget::ConstructNewTreeLevel(UVerticalBox* tree_box)
{
	if (tree_box == nullptr)
	{
		return nullptr;
	}

	UHorizontalBox* level_box = WidgetTree->ConstructWidget<UHorizontalBox>();
	UVerticalBoxSlot* level_box_slot = tree_box->AddChildToVerticalBox(level_box);
	if (level_box_slot)
	{
		level_box_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		level_box_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	return level_box;
}

UButton* UPerkUnlockWidget::ConstructNewTreeNode(UHorizontalBox* level_box)
{
	if (level_box == nullptr)
	{
		return nullptr;
	}

	UButton* node = WidgetTree->ConstructWidget<UButton>();
	// Default node style does not have image info
	node->SetStyle(default_node_style);
	UHorizontalBoxSlot* node_slot = level_box->AddChildToHorizontalBox(node);
	if (node_slot)
	{
		node_slot->SetPadding(FMargin(64.f));
	}

	return node;
}

void UPerkUnlockWidget::ConstructLink(UButton* start, UButton* end)
{
	if (start == nullptr || end == nullptr)
	{
		return;
	}

	FVector2D start_position = start->GetParent()->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0))
		+ start->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.5, 0.5));
	start_position.X -= start->GetParent()->GetParent()->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.5)).X;

	FVector2D end_position = end->GetParent()->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0))	// Position of level box(horizontal box)
		+ end->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.5, 0.5)); // Points to center of nodes (size / 2)
	end_position.X -= end->GetParent()->GetParent()->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.5)).X; // Center alignment (offset to follow top-center anchor)

	FVector2D direction = end_position - start_position;
	float angle = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));

	UProgressBar* link = WidgetTree->ConstructWidget<UProgressBar>();
	link->SetRenderTransformAngle(angle);
	link->SetRenderTransformPivot(FVector2D(0.0, 0.5));
	link->SetPercent(0.f);
	UCanvasPanelSlot* link_slot = scroll_panel_->AddChildToCanvas(link);
	if (link_slot)
	{
		// Top-center anchor
		link_slot->SetAnchors(FAnchors(0.5f, 0.f));
		link_slot->SetSize(FVector2D(direction.Size(), 15.f));
		link_slot->SetPosition(start_position);
	}
}
