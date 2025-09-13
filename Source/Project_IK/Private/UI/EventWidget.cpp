/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Level Widget class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EventWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "Structs/EventData.h"
#include "WorldSettings/IKGameInstance.h"

#include "Subsystems/LevelTransitionSubsystem.h"

void UEventWidget::InitEventWidget(FEventData input_data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	situation_->SetBrushFromTexture(input_data.situation_);
	event_title_->SetText(text_manager->GetEventNameText(input_data.event_type_));
	text_body_->SetText(text_manager->GetEventDetailText(input_data.event_type_));
	first_option_->SetText(text_manager->GetEventOptionText(input_data.event_type_, 0));
	second_option_->SetText(text_manager->GetEventOptionText(input_data.event_type_, 1));
	third_option_->SetText(text_manager->GetEventOptionText(input_data.event_type_, 2));
	fourth_option_->SetText(text_manager->GetEventOptionText(input_data.event_type_, 3));
}

void UEventWidget::ClearButtonBinding()
{
	if (button_1_->OnClicked.IsBound())
	{
		button_1_->OnClicked.Clear();
	}
	if (button_2_->OnClicked.IsBound())
	{
		button_2_->OnClicked.Clear();
	}
	if (button_3_->OnClicked.IsBound())
	{
		button_3_->OnClicked.Clear();
	}
	if (button_4_->OnClicked.IsBound())
	{
		button_4_->OnClicked.Clear();
	}
	if (end_button_->OnClicked.IsBound())
	{
		end_button_->OnClicked.Clear();
	}
}

void UEventWidget::EnableButtons(int32 num)
{
	TArray<UButton*> buttons{ button_1_, button_2_, button_3_, button_4_ };
	int32 begin = FMath::Min(num, buttons.Num());
	for (int32 i = begin; i < buttons.Num(); i++)
	{
		buttons[i]->SetIsEnabled(false);
		buttons[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UEventWidget::NativeConstruct()
{
	Super::NativeConstruct();
	end_button_->OnClicked.AddDynamic(this, &UEventWidget::OnEndButtonClicked);
}

void UEventWidget::NativeDestruct()
{
	ClearButtonBinding();
	Super::NativeDestruct();
}

void UEventWidget::OnEndButtonClicked()
{
	GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
}
