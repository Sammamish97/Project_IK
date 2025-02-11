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
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "WorldSettings/IKGameInstance.h"
#include "Managers/EnumCluster.h"
#include "Managers/TextureManager.h"
#include "Managers/InventoryManager.h"
#include "Managers/CharacterDataManager.h"

#include "UI/ConfirmationWidget.h"

#include "Subsystems/PerkTreeSubsystem.h"


void UPerkUnlockWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConstructLinks();
	ConstructPerkTree();

	link_animation_percent_ = 0.f;
	current_hero_type_ = EHeroType::Hero1;
	left_button_->OnClicked.AddDynamic(this, &UPerkUnlockWidget::OnLeftButtonClicked);
	right_button_->OnClicked.AddDynamic(this, &UPerkUnlockWidget::OnRightButtonClicked);

	path_to_selected_node_.Empty();

	UpdateHeroData();

	perk_points_text_->SetText(FText::FromString(FString::FromInt(
		Cast<UIKGameInstance>(GetGameInstance())->GetInventoryManager()->GetPerkPoints()
	)));


	if (confirmation_widget_class_)
	{
		confirmation_widget_ = WidgetTree->ConstructWidget<UConfirmationWidget>(confirmation_widget_class_);
		confirmation_widget_->OnConfirmation.AddDynamic(this, &UPerkUnlockWidget::OnConfirmed);
	}
}

void UPerkUnlockWidget::NativeDestruct()
{
	Super::NativeDestruct();

	ClearButtonDelegates();

	GetWorld()->GetTimerManager().ClearTimer(link_animation_timer_handle_);

	if (confirmation_widget_->OnConfirmation.IsBound())
	{
		confirmation_widget_->OnConfirmation.Clear();
	}
}

void UPerkUnlockWidget::ConstructPerkTree()
{
	TArray<FPerkNode> tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	// Initialize button array with nullptr
	buttons_.Init(nullptr, tree.Num());

	UVerticalBox* tree_box = ConstructNewTreeBox();

	// node on 0 index in tree is root node of the tree
	TArray<FPerkNode> current_level_nodes({ tree[0] });
	TArray<TObjectPtr<UButton>*> pointer_to_content_of_button_array({ &buttons_[0] });
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
			CustomizeButtonByNode(button, current_level_nodes[i]);
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
	TArray<FPerkNode> tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();


	int32 level = 0;
	TArray<FPerkNode> current_level_nodes({ tree[0] });
	TArray<int32> current_indices({ 0 });
	while (current_level_nodes.IsEmpty() == false)
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
	node->SetStyle(lockable_node_style_);
	node->OnClicked.AddDynamic(this, &UPerkUnlockWidget::OnButtonClicked);
	UHorizontalBoxSlot* node_slot = level_box->AddChildToHorizontalBox(node);
	if (node_slot)
	{
		node_slot->SetPadding(node_margin_);
	}

	return node;
}

void UPerkUnlockWidget::CustomizeButtonByNode(UButton* button, const FPerkNode& node)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!game_instance)
	{
		return;
	}

	UTexture2D* texture = game_instance->GetTextureManager()->GetBuffTexture(node.stat_);
	if (texture)
	{
		FButtonStyle style = button->GetStyle();
		style.Normal.SetResourceObject(texture);
		button->SetStyle(style);
	}
}

UProgressBar* UPerkUnlockWidget::ConstructLink(int32 start_index, int32 start_max_index, int32 end_index, int32 end_max_index, int32 level)
{
	FVector2D start_position = CalculateNodePosition(start_index, start_max_index, level);
	FVector2D end_position = CalculateNodePosition(end_index, end_max_index, level + 1);

	FVector2D direction = end_position - start_position;
	float angle = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));

	UProgressBar* link = WidgetTree->ConstructWidget<UProgressBar>();
	link->SetWidgetStyle(lockable_progress_bar_style_);
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
	FVector2D node_size = lockable_node_style_.Normal.GetImageSize() + node_margin_.GetDesiredSize2f();

	FVector2D result;
	result.X = index * node_size.X - ((node_size.X * size) / 2.f);
	result.Y = node_size.Y * level;

	result += node_size / 2.f;

	return result;
}

void UPerkUnlockWidget::OnButtonClicked()
{
	path_to_selected_node_.Empty();
	OnButtonClickedDFS(GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree(), 0, path_to_selected_node_);
}

void UPerkUnlockWidget::OnConfirmed()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());
	const int32 perk_points = game_instance->GetInventoryManager()->GetPerkPoints();
	const int32 clicked_perk_points = GetAccumulatedPerkCost(path_to_selected_node_.Top());
	if (clicked_perk_points <= perk_points)
	{
		for (int32 node_index : path_to_selected_node_)
		{
			UnlockPerk(node_index);
		}
		game_instance->GetInventoryManager()->SetPerkPoints(perk_points - clicked_perk_points);

		perk_points_text_->SetText(FText::FromString(FString::FromInt(
			perk_points - clicked_perk_points
		)));


		UpdateCosts(GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>()->GetProgress(current_hero_type_));
		LockUnpayableButtons();
	}
	else
	{
		// @@ TODO: Add VFX/SFX to indicate insufficient perk points.
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

	if (left_button_->OnClicked.IsBound())
	{
		left_button_->OnClicked.Clear();
	}
	if (right_button_->OnClicked.IsBound())
	{
		right_button_->OnClicked.Clear();
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

void UPerkUnlockWidget::OnLeftButtonClicked()
{
	switch (current_hero_type_)
	{
	case EHeroType::Hero1:
		current_hero_type_ = EHeroType::Hero4;
		break;
	case EHeroType::Hero2:
		current_hero_type_ = EHeroType::Hero1;
		break;
	case EHeroType::Hero3:
		current_hero_type_ = EHeroType::Hero2;
		break;
	case EHeroType::Hero4:
		current_hero_type_ = EHeroType::Hero3;
		break;
	case EHeroType::INVALID:
	default:
		current_hero_type_ = EHeroType::Hero1;
		break;
	}

	UpdateHeroData();
}

void UPerkUnlockWidget::OnRightButtonClicked()
{
	switch (current_hero_type_)
	{
	case EHeroType::Hero1:
		current_hero_type_ = EHeroType::Hero2;
		break;
	case EHeroType::Hero2:
		current_hero_type_ = EHeroType::Hero3;
		break;
	case EHeroType::Hero3:
		current_hero_type_ = EHeroType::Hero4;
		break;
	case EHeroType::Hero4:
	case EHeroType::INVALID:
	default:
		current_hero_type_ = EHeroType::Hero1;
		break;
	}

	UpdateHeroData();
}

void UPerkUnlockWidget::UpdateHeroData()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!game_instance)
	{
		return;
	}

	FString text_name;
	// @@ TODO: set appropriate text name by Enum
	switch (current_hero_type_)
	{
	case EHeroType::Hero1:
		text_name = "default_portrait_1";
		break;
	case EHeroType::Hero2:
		text_name = "default_portrait_2";
		break;
	case EHeroType::Hero3:
		text_name = "default_portrait_3";
		break;
	case EHeroType::Hero4:
		text_name = "default_portrait_4";
		break;
	default:
		// Error text
		text_name = "default_portrait";
		break;
	}

	portrait_image_->SetBrushFromTexture(game_instance->GetTextureManager()->GetTexture(text_name));


	ClearWidgets();

	UPerkProgressSubsystem* perk_progress_system = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	if (perk_progress_system)
	{
		TSet<int32> progress = perk_progress_system->GetProgress(current_hero_type_);
		// Unlock buttons by recorded progress
		for (int32 activated_node : progress)
		{
			MakeButtonUnlockedVisually(activated_node);
		}

		// Lock unpayable buttons by using both progress and tree costs.
		UpdateCosts(progress);
		LockUnpayableButtons();
	}
}

// It returns false when progress already recorded.
bool UPerkUnlockWidget::UnlockPerk(int32 clicked_index)
{
	MakeButtonUnlockedVisually(clicked_index, true);

	UPerkProgressSubsystem* perk_progress_system = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	if (!perk_progress_system)
	{
		return false;
	}
	bool successfully_added = perk_progress_system->AddProgress(current_hero_type_, clicked_index);
	if (!successfully_added)
	{
		return false;
	}

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());
	const TArray<FPerkNode>& tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();
	if (game_instance)
	{
		game_instance->GetCharacterDataManager()->EnhanceCharacterData(current_hero_type_, tree[clicked_index].stat_, tree[clicked_index].modifier_);
	}

	return true;
}

void UPerkUnlockWidget::MakeButtonUnlockedVisually(int32 clicked_index, bool is_animate_links)
{
	if (buttons_[clicked_index]->GetIsEnabled() == false)
	{
		return;
	}

	TArray<FPerkNode> tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();
	if (is_animate_links)
	{
		TArray<TWeakObjectPtr<UProgressBar>> links;
		for (int32 next_index : tree[clicked_index].next_)
		{
			links.Add(links_[FIntPoint(clicked_index, next_index)]);
		}
		StartLinkAnimation(links);
	}
	else
	{
		for (int32 next_index : tree[clicked_index].next_)
		{
			links_[FIntPoint(clicked_index, next_index)]->SetPercent(1.f);
		}
	}

	FButtonStyle unlocked_button_style = buttons_[clicked_index]->GetStyle();
	unlocked_button_style.SetDisabled(unlocked_disabled_brush_);
	buttons_[clicked_index]->SetStyle(unlocked_button_style);
	buttons_[clicked_index]->SetIsEnabled(false);
}

void UPerkUnlockWidget::ClearWidgets()
{
	for (TObjectPtr<UButton> button : buttons_)
	{
		button->SetIsEnabled(true);
	}
	for (TPair<FIntPoint, TObjectPtr<UProgressBar>> link : links_)
	{
		link.Value->SetPercent(0.f);
		link.Value->SetWidgetStyle(lockable_progress_bar_style_);
	}

	links_animating_.Empty();
}

int32 UPerkUnlockWidget::GetAccumulatedPerkCost(int32 perk_index)
{
	return costs_[perk_index];
}

void UPerkUnlockWidget::UpdateCosts(const TSet<int32>& progress)
{
	TArray<FPerkNode> tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	if (costs_.Num() < tree.Num())
	{
		costs_.Init(0, tree.Num());
	}

	AccumulateCost(tree, progress, 0, 0);
}

void UPerkUnlockWidget::AccumulateCost(const TArray<FPerkNode>& tree, const TSet<int32>& progress, int32 current_node_index, int32 accumulated_cost)
{
	if (!progress.Contains(current_node_index))
	{
		accumulated_cost += tree[current_node_index].cost_;
	}

	costs_[current_node_index] = accumulated_cost;

	for (int32 next_index : tree[current_node_index].next_)
	{
		AccumulateCost(tree, progress, next_index, accumulated_cost);
	}
}

void UPerkUnlockWidget::LockUnpayableButtons()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());
	const int32 perk_points = game_instance->GetInventoryManager()->GetPerkPoints();
	TArray<FPerkNode> tree = GetGameInstance()->GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	for (int32 i = 0; i < tree.Num(); i++)
	{
		if (perk_points < costs_[i] && buttons_[i]->GetIsEnabled())
		{
			// It is Unpayable. Lock them all.
			FButtonStyle style = buttons_[i]->GetStyle();
			style.SetDisabled(locked_disabled_brush_);
			buttons_[i]->SetStyle(style);
			buttons_[i]->SetIsEnabled(false);

			for (int32 next_index : tree[i].next_)
			{
				links_[FIntPoint(i, next_index)]->SetWidgetStyle(locked_progress_bar_style_);
			}
		}
	}
}

bool UPerkUnlockWidget::OnButtonClickedDFS(const TArray<FPerkNode>& tree, int32 current_node_index, TArray<int32>& path)
{
	path.Add(current_node_index);

	if (buttons_[current_node_index]->IsHovered())
	{
		if (confirmation_widget_)
		{
			const int32 clicked_perk_points = GetAccumulatedPerkCost(current_node_index);
			FText confirm_text = FText::Format(FText::FromString("Are you sure you want to unlock the perk? It costs {0}"), FText::AsNumber(clicked_perk_points));
			confirmation_widget_->SetText(confirm_text);
			confirmation_widget_->AddToViewport();
		}

		return true;
	}

	for (int32 next_node_index : tree[current_node_index].next_)
	{
		if (OnButtonClickedDFS(tree, next_node_index, path))
		{
			return true;
		}
	}

	path.Pop();

	return false;
}
