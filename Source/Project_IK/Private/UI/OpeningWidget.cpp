/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.29.2025
Summary : Source file for opening widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/OpeningWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystems/LevelTransitionSubsystem.h"

void UOpeningWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
	counter_ = 0;
	image_->SetBrushFromTexture(images_[counter_]);

	if (fade_in_)
	{
		FWidgetAnimationDynamicEvent Done;
		Done.BindDynamic(this, &UOpeningWidget::OnFadeInFinished);
		BindToAnimationFinished(fade_in_, Done);
	}
	if (fade_out_)
	{
		FWidgetAnimationDynamicEvent Done;
		Done.BindDynamic(this, &UOpeningWidget::OnFadeOutFinished);
		BindToAnimationFinished(fade_out_, Done);
	}
	PlayFadeIn();
}

void UOpeningWidget::PlayFadeIn(float PlayRate)
{
	if (!fade_in_)
	{
		return;
	}
	subtitle_->SetText(text_manager_cache_->GetOpeningText(counter_));

	PlayAnimation(fade_in_,0.0f,1, EUMGSequencePlayMode::Forward,PlayRate, false);
}

void UOpeningWidget::PlayFadeOut(float PlayRate)
{
	if (!fade_out_)
	{
		return;
	}
	PlayAnimation(fade_out_, 0.f,1, EUMGSequencePlayMode::Forward, PlayRate, false);
}

FReply UOpeningWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (counter_ < 4)
	{
		counter_ += 1;
		image_->SetBrushFromTexture(images_[counter_]);
		subtitle_->SetText(text_manager_cache_->GetOpeningText(counter_));
	}
	else
	{
		ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
		level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::LobbyLevel);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UOpeningWidget::OnFadeInFinished()
{
	PlayFadeOut();
}

void UOpeningWidget::OnFadeOutFinished()
{
	if (counter_ < 4)
	{
		counter_ += 1;
		image_->SetBrushFromTexture(images_[counter_]);
		PlayFadeIn();
	}
	else
	{
		ULevelTransitionSubsystem* level_transition_subsystem = GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
		level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::LobbyLevel);
	}
}