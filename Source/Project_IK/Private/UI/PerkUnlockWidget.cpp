/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for UI to unlock heros' perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/PerkUnlockWidget.h"

#include "Subsystems/PerkProgressSubsystem.h"

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

	ConstructLinks();
	ConstructPerkTree();


	// @@ TODO: Connect this UI to Perk Progress system.
	UPerkProgressSubsystem* perk_progress_system = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	if (perk_progress_system)
	{
		TSet<int32> progress = perk_progress_system->GetProgress(EHeroType::Hero1);
	}

	link_animation_percent_ = 0.f;
}

void UPerkUnlockWidget::NativeDestruct()
{
	Super::NativeDestruct();

	ClearButtonDelegates();

	GetWorld()->GetTimerManager().ClearTimer(link_animation_timer_handle_);
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


	int32 level = 0;
	TArray<FPerkNode> current_level_nodes({tree[0]});
	TArray<int32> current_indices({ 0 });
	while(current_level_nodes.IsEmpty() == false)
	{
		TArray<FPerkNode> next_level_nodes;
		TArray<int32> next_indices;

		// A loop to create next level data
		const int32 current_size = current_level_nodes.Num();
		for (int32 current_index = 0; current_index < current_size; current_index++)
		{
			const int32 next_size = current_level_nodes[current_index].next_.Num();

			for (int32 next_index = 0; next_index < next_size; next_index++)
			{
				// Update next nodes
				next_level_nodes.Add(tree[current_level_nodes[current_index].next_[next_index]]);
				next_indices.Add(current_level_nodes[current_index].next_[next_index]);
			}
		}

		// A loop creating links using both current node data and next node data.
		int32 index = 0;
		for (int32 current_index = 0; current_index < current_size; current_index++)
		{
			for (int32 iterator : current_level_nodes[current_index].next_)
			{
				UProgressBar* link = ConstructLink(current_index, current_size, index, next_level_nodes.Num(), level);
				if (link)
				{
					links_.Add(FIntPoint(current_indices[current_index], next_indices[index]), link);
				}

				++index;
			}
		}

		current_level_nodes = MoveTemp(next_level_nodes);
		current_indices = MoveTemp(next_indices);
		++level;
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
	node->SetStyle(default_node_style_);
	node->OnClicked.AddDynamic(this, &UPerkUnlockWidget::OnButtonClicked);
	UHorizontalBoxSlot* node_slot = level_box->AddChildToHorizontalBox(node);
	if (node_slot)
	{
		node_slot->SetPadding(node_margin_);
	}

	return node;
}

UProgressBar* UPerkUnlockWidget::ConstructLink(int32 start_index, int32 start_max_index, int32 end_index, int32 end_max_index, int32 level)
{
	FVector2D start_position = CalculateNodePosition(start_index, start_max_index, level);
	FVector2D end_position = CalculateNodePosition(end_index, end_max_index, level + 1);

	FVector2D direction = end_position - start_position;
	float angle = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));

	UProgressBar* link = WidgetTree->ConstructWidget<UProgressBar>();
	link->SetFillColorAndOpacity(link_fill_color_);
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

	return link;
}

FVector2D UPerkUnlockWidget::CalculateNodePosition(int32 index, int32 size, int32 level)
{
	FVector2D node_size = default_node_style_.Normal.GetImageSize() + node_margin_.GetDesiredSize2f();

	FVector2D result;
	result.X = index * node_size.X - ((node_size.X * size) / 2.f);
	result.Y = node_size.Y * level;

	result += node_size / 2.f;

	return result;
}

void UPerkUnlockWidget::OnButtonClicked()
{
	for (int32 i = 0; i < buttons_.Num(); ++i)
	{
		if (buttons_[i]->IsHovered())
		{
			TArray<FPerkNode> tree = UPerkTree::Get()->GetTree();
			TArray<TWeakObjectPtr<UProgressBar>> links;
			for (int32 next_index : tree[i].next_)
			{
				links.Add(links_[FIntPoint(i, next_index)]);
			}
			StartLinkAnimation(links);
		}
	}

}

void UPerkUnlockWidget::ClearButtonDelegates()
{
	for (UButton* button : buttons_)
	{
		if (button->OnClicked.IsBound())
		{
			button->OnClicked.Clear();
		}
	}
}

void UPerkUnlockWidget::StartLinkAnimation(TArray<TWeakObjectPtr<UProgressBar>> links)
{
	if (!links_animating_.IsEmpty())
	{
		// Clean up not yet fully animated links
		for (TWeakObjectPtr<UProgressBar> link : links_animating_)
		{
			link->SetPercent(1.f);
		}
	}

	links_animating_ = MoveTemp(links);
	link_animation_percent_ = 0.f;

	for (TWeakObjectPtr<UProgressBar> link : links_animating_)
	{
		link->SetPercent(link_animation_percent_);
	}

	GetWorld()->GetTimerManager().SetTimer(link_animation_timer_handle_, this, &UPerkUnlockWidget::UpdateLinkAnimation, link_animation_interval_, true);
}

void UPerkUnlockWidget::UpdateLinkAnimation()
{
	link_animation_percent_ += link_animation_interval_;

	for (TWeakObjectPtr<UProgressBar> link : links_animating_)
	{
		link->SetPercent(link_animation_percent_);
	}

	if (link_animation_percent_ >= 1.f)
	{
		links_animating_.Empty();
		GetWorld()->GetTimerManager().ClearTimer(link_animation_timer_handle_);
	}
}
