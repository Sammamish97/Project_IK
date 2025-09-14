/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Source file for Global Buff Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/PopUps/GlobalBuffPopupWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "WorldSettings/IKGameInstance.h"

void UGlobalBuffPopupWidget::UpdateLeftDuration(int32 left_duration)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	FText cool_down_base = text_manager->GetPopUpText("GBUFF_DURATION");

	FFormatNamedArguments args;
	args.Add("GBUFF_DURATION", FText::AsNumber(left_duration));
	left_duration_text_->SetText( FText::Format(cool_down_base, args));
}
