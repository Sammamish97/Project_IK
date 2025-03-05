/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Source file for Combat Result UI class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/CombatResultUI.h"

// UI widget components
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/BorderSlot.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "UI/CombatResultBlock.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"
#include "Managers/CombatLevelResultManager.h"


bool UCombatResultUI::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}

	InitializeRootWidget();

	return true;
}

void UCombatResultUI::SetHeroNumbers(int32 num)
{
	UCanvasPanelSlot* UI_background_slot = Cast<UCanvasPanelSlot>(UI_background_->Slot);
	if (UI_background_slot)
	{
		UI_background_slot->SetPosition(FVector2D(num * -200.0, -400.0));
		UI_background_slot->SetSize(FVector2D(num * 400.0, 800.0));
	}

	if (combat_result_block_widget_class_)
	{
		for (int32 i = 0; i < num; i++)
		{
			UCombatResultBlock* block = CreateWidget<UCombatResultBlock>(this, combat_result_block_widget_class_);
			FString block_unique_name = MakeUniqueObjectName(GetOuter(), block->GetClass(), TEXT("Block")).ToString();
			block->Rename(*block_unique_name);
			UHorizontalBoxSlot* block_slot = blocks_holder_->AddChildToHorizontalBox(block);
			block_slot->SetPadding(FMargin(32.f));

			blocks_.Add(block);
		}
	}
}

void UCombatResultUI::UpdateResults(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map)
{
	const int32 hero_num = heroes.Num();
	for (int32 i = 0; i < hero_num; ++i)
	{
		// Nullptr check
		AHeroBase* hero = Cast<AHeroBase>(heroes[i]);
		if (hero)
		{
			blocks_[i]->SetVisibility(ESlateVisibility::Visible);
			const UCharacterStatComponent* hero_stat = hero->GetCharacterStat();
			hp_ratio_after_.Add(hero_stat->GetHPRatio());
			if (damage_map.Contains(hero))
			{
				blocks_[i]->SetDamageDealt(damage_map[hero]);
			}
			else
			{
				blocks_[i]->SetDamageDealt(0.f);
			}
		}
		else
		{
			// Consider the hero has dead
			blocks_[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	while (hp_ratio_after_.Num() < hp_ratio_before_.Num())
	{
		hp_ratio_after_.Add(0.f);
	}

	HP_timer_ = 0;
}

void UCombatResultUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsVisible())
	{
		return;
	}

	UpdateHPBars(InDeltaTime);
}

void UCombatResultUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeChildWidgets();


	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (game_mode)
	{
		TArray<AActor*> hero_containers = game_mode->GetHeroContainers();
		for (int32 i = 0; i < hero_containers.Num(); i++)
		{
			AHeroBase* hero = Cast<AHeroBase>(hero_containers[i]);
			// It is not ratio at this point. It contains initial hit points.
			hp_ratio_before_.Add(hero->GetCharacterStat()->GetHPRatio());
		}

		int32 hero_size = game_mode->GetHeroContainers().Num();
		// @@ TODO: In this code, it is possible to have multiple blocks because of multiple NativeConstruct calls.
							// Need to delete data in NativeDestruct.
		SetHeroNumbers(hero_size);
	}

}

void UCombatResultUI::InitializeRootWidget()
{
	root_canvas_panel_ = WidgetTree->ConstructWidget<UCanvasPanel>();
	root_canvas_panel_->Rename(*MakeUniqueObjectName(GetOuter(), root_canvas_panel_->GetClass(), TEXT("Root canvas panel")).ToString());
	WidgetTree->RootWidget = root_canvas_panel_.Get();
}

void UCombatResultUI::InitializeChildWidgets()
{
	// Initialize outlines
	UI_background_ = NewObject<UBorder>();
	UI_background_->Rename(*MakeUniqueObjectName(GetOuter(), UI_background_->GetClass(), TEXT("UI Background")).ToString());
	UI_background_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	UI_background_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.4f));
	UCanvasPanelSlot* UI_background_slot = root_canvas_panel_->AddChildToCanvas(UI_background_.Get());
	if (UI_background_slot)
	{
		UI_background_slot->SetAnchors(FAnchors(0.5f, 0.5f));
	}

	widgets_holder_ = NewObject<UVerticalBox>();
	widgets_holder_->Rename(*MakeUniqueObjectName(GetOuter(), widgets_holder_->GetClass(), TEXT("Widgets holder")).ToString());
	UBorderSlot* widgets_holder_slot = Cast<UBorderSlot>(UI_background_->AddChild(widgets_holder_.Get()));
	if (widgets_holder_slot)
	{
		widgets_holder_slot->SetPadding(FMargin(4.0, 2.0));
		widgets_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	}


	// Initialize title texts
	title_holder_ = NewObject<UBorder>();
	title_holder_->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	title_holder_->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	title_holder_->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
	UVerticalBoxSlot* title_holder_slot = widgets_holder_->AddChildToVerticalBox(title_holder_.Get());
	if (title_holder_slot)
	{
		title_holder_slot->SetPadding(FMargin(0.0, 64.0, 0.0, -64.0));
	}

	title_ = NewObject<UTextBlock>();
	title_->SetText(FText::FromString("Combat Result"));
	UBorderSlot* title_slot = Cast<UBorderSlot>(title_holder_->AddChild(title_.Get()));
	if (title_slot)
	{
		title_slot->SetPadding(FMargin(4.0f, 2.0f));
		title_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		title_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}

	// Initialize a block holder
	blocks_holder_ = NewObject<UHorizontalBox>();
	UVerticalBoxSlot* blocks_holder_slot = widgets_holder_->AddChildToVerticalBox(blocks_holder_.Get());
	if (blocks_holder_slot)
	{
		blocks_holder_slot->SetSize(FSlateChildSize());
		blocks_holder_slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		blocks_holder_slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
}


// Diminishes HP slowly (0s ~ 1s), Stops for 2 seconds (1s ~ 3s)
// Blink it if in low when stopped.
void UCombatResultUI::UpdateHPBars(float InDeltaTime)
{
	HP_timer_ += InDeltaTime;

	if (HP_timer_ >= 3.f)
	{
		HP_timer_ = 0.f;
	}

	if (HP_timer_ <= 1.f)
	{
		for (int32 i = 0; i < blocks_.Num(); i++)
		{
			float hp = FMath::Lerp(hp_ratio_before_[i], hp_ratio_after_[i], HP_timer_);
			if (blocks_[i].IsValid())
			{
				blocks_[i]->SetHPPercent(hp);
			}
		}
	}
	else if (HP_timer_ >= 1.25f && HP_timer_ <= 1.75)
	{
		float opacity = FMath::Abs((HP_timer_ - 1.5f) * 4);
		for (int32 i = 0; i < blocks_.Num(); i++)
		{
			if (blocks_[i].IsValid())
			{
				if (blocks_[i]->GetHPPercent() < 0.25f)
				{
					blocks_[i]->SetHPOpacity(opacity);
				}
			}
		}
	}
	else if (HP_timer_ >= 2.25f && HP_timer_ <= 2.75f)
	{
		float opacity = FMath::Abs((HP_timer_ - 2.5f) * 4);
		for (int32 i = 0; i < blocks_.Num(); i++)
		{
			if (blocks_[i].IsValid())
			{
				if (blocks_[i]->GetHPPercent() < 0.25f)
				{
					blocks_[i]->SetHPOpacity(opacity);
				}
			}
		}
	}
}

FReply UCombatResultUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (hud)
		{
			hud->SwitchUIByState(ELevelEndState::ShowingItemPickerUI);

			return FReply::Handled();
		}

	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
