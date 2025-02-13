/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.07.2025
Summary : Source file for a widget to display credits.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/CreditWidget.h"

#include "WorldSettings/IKGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/HeroInventoryManager.h"

#include "Components/TextBlock.h"

void UCreditWidget::UpdateCreditText()
{
	if (inventory_manager_.IsValid())
	{
		const int32 credits = inventory_manager_->GetCredits();
		credit_text_->SetText(FText::FromString(FString::FromInt(credits)));
	}
}

void UCreditWidget::NativeConstruct()
{
	Super::NativeConstruct();


	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	inventory_manager_ = game_instance->GetInventoryManager();
	UpdateCreditText();
}
