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
#include "Managers/CombatLevelResultManager.h"

#include "Managers/EnumCluster.h"

#include "Subsystems/GlobalBuffSubsystem.h"


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

void UCombatResultUI::PopulateWidgets(const TArray<TObjectPtr<AActor>>& hero_containers)
{	// Synchronize blocks num to be HeroType now.
	for(int32 i = 0; i < 4; ++i)
	{
		hp_ratio_after_.Add(0.f);

		if (hero_containers[i] == nullptr)
		{
			hp_ratio_before_.Add(0.f);
			continue;
		}

		if (AHeroBase* hero = Cast<AHeroBase>(hero_containers[i]))
		{
			// It contains initial hit points ratio.
			hp_ratio_before_.Add(hero->GetCharacterStat()->GetHPRatio());
		}
	}

	if (combat_result_block_widget_class_)
	{
		for(int32 i = 0; i < 4; ++i)
		{
			if (hero_containers[i] == nullptr)
			{
				blocks_.Add(nullptr);
			}
			else
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

	UCanvasPanelSlot* UI_background_slot = Cast<UCanvasPanelSlot>(UI_background_->Slot);
	if (UI_background_slot)
	{
		UI_background_slot->SetPosition(FVector2D(blocks_holder_->GetChildrenCount() * -200.0, -400.0));
		UI_background_slot->SetSize(FVector2D(blocks_holder_->GetChildrenCount() * 400.0, 800.0));
	}
}

void UCombatResultUI::UpdateResults(const TMap<EHeroType, float>& damage_map)
{
	// Update damage records.
	for (const auto& [hero_type, damage] : damage_map)
	{
		int32 hero_index = HeroTypeToInt(hero_type);

		blocks_[hero_index]->SetDamageDealt(damage);
	}

	// Update HP after battles
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	const auto& hero_container = game_mode->GetHeroContainer();
	for (const auto& hero_map_elem : hero_container)
	{
		if(AHeroBase* hero = Cast<AHeroBase>(hero_map_elem))
		{
			if (hero)
			{
				hp_ratio_after_[HeroTypeToInt(hero->GetHeroType())] = hero->GetCharacterStat()->GetHPRatio();
			}
		}
	}

	UGlobalBuffSubsystem* global_buff_subsystem = GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	// Update injury status
	for (int32 i = 0; i < blocks_.Num(); i++)
	{
		if (blocks_[i] && hp_ratio_after_[i] <= 0.f)
		{
			blocks_[i]->SetHoveredTextVisibility(ESlateVisibility::Visible);

			// Need to check through GlobalBuff instead of SpawnData because of function call sequence
			if (global_buff_subsystem->HasBuff(HeroTypeToDeathbound(IntToHeroType(i))))
			{
				blocks_[i]->SetHoveredText(NSLOCTEXT("UI", "CombatResultUIDead", "Dead"));
			}
			else
			{
				blocks_[i]->SetHoveredText(NSLOCTEXT("UI", "CombatResultUIInjured", "Injured"));
			}
		}
	}

	HP_timer_ = 0.f;
	injury_timer_ = 0.f;
}

void UCombatResultUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsVisible())
	{
		return;
	}

	UpdateHPBars(InDeltaTime);
	UpdateInjuredNotifiers(InDeltaTime);
}

void UCombatResultUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeChildWidgets();

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (game_mode)
	{
		PopulateWidgets(game_mode->GetHeroContainer());
	}
}

void UCombatResultUI::NativeDestruct()
{
	blocks_.Empty();
	hp_ratio_before_.Empty();
	hp_ratio_after_.Empty();
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
	title_->SetText(NSLOCTEXT("UI", "CombatResultTitle", "Combat Result"));
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
			if (blocks_[i])
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
			if (blocks_[i])
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
			if (blocks_[i])
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
		AIKGameModeBase* gamemode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (gamemode)
		{
			gamemode->ProceedGameFlowAfterUI();
		}

	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

// Fade in (0s~1.5s), fade out (1.5s~3s)
void UCombatResultUI::UpdateInjuredNotifiers(float InDeltaTime)
{
	injury_timer_ += InDeltaTime;

	static constexpr float FADE_DURATION = 1.5f;

	float alpha = 0.f;
	if (injury_timer_ <= FADE_DURATION)
	{	// Fade in
		alpha = injury_timer_ / FADE_DURATION;
	}
	else if (injury_timer_ > FADE_DURATION * 2.f)
	{
		injury_timer_ = 0.f;
	}
	else
	{	// Fade out
		alpha = 1.f - ((injury_timer_ - FADE_DURATION) / FADE_DURATION);
	}

	for (int32 i = 0; i < blocks_.Num(); i++)
	{
		if (blocks_[i] && hp_ratio_after_[i] <= 0.f)
		{
			blocks_[i]->SetHoveredTextOpacity(alpha);
		}
	}
}
