/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Source file for Support skill Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/SupportSkillPopupWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "WorldSettings/IKGameInstance.h"

void USupportSkillPopupWidget::UpdateCost(int32 cost)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	FText cool_down_base = text_manager->GetPopUpText("Cost");

	FFormatNamedArguments args;
	args.Add("Cost", FText::AsNumber(cost));
	cost_text_->SetText( FText::Format(cool_down_base, args));
}
