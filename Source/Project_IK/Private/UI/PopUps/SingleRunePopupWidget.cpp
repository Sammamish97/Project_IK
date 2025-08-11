/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.11.2025
Summary : Source file for Single Rune Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/SingleRunePopupWidget.h"

#include "Components/RichTextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TextManager.h"
#include "WorldSettings/IKGameInstance.h"

void USingleRunePopupWidget::UpdateRuneData(ERuneSetType rune_type, ERuneSetBonusType set_type)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();

	name_->SetText(text_manager->GetRuneNameText(rune_type));
	
	edge_name_->SetText(text_manager->GetPopUpText("EDGE"));
	triangle_name_->SetText(text_manager->GetPopUpText("TRIANGLE"));
	hexagon_name_->SetText(text_manager->GetPopUpText("HEXAGON"));

	edge_bonus_->SetText(text_manager->GetRuneSetBonusText(rune_type, ERuneSetBonusType::Edge));
	triangle_bonus_->SetText(text_manager->GetRuneSetBonusText(rune_type, ERuneSetBonusType::Triangle));
	hexagon_bonus_->SetText(text_manager->GetRuneSetBonusText(rune_type, ERuneSetBonusType::Hexagon));
}
