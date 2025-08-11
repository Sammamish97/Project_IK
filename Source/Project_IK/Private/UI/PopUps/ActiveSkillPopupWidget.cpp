/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Source file for Active Skill Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/ActiveSkillPopupWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextManager.h"
#include "Components/TextBlock.h"

void UActiveSkillPopupWidget::UpdateCoolDown(float cool_time)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	FText cool_down_base = text_manager->GetPopUpText("CoolTime");

	FFormatNamedArguments args;
	args.Add("CoolTime", FText::AsNumber(cool_time));
	cool_time_text_->SetText( FText::Format(cool_down_base, args));
}
