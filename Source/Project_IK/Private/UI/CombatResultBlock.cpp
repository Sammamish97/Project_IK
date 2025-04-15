/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Source file for Combat Result block class.
						It is an attachment for CombatResultUI. It is not be used itself alone.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/CombatResultBlock.h"

#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Spacer.h"
#include "Components/SizeBox.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"

void UCombatResultBlock::SetHPPercent(float ratio)
{
	// @@ TODO: Make it function
	// 10% Red, 90% Green
	hp_->SetPercent(ratio);
	ratio -= 0.5f;
	ratio *= 5.f / 4.f;
	ratio = FMath::Clamp(ratio, -0.5f, 0.5f);
	ratio += 0.5f;

	FLinearColor hp_color = FMath::Lerp(FLinearColor(1.f, 0.f, 0.f), FLinearColor(0.f, 1.f, 0.f), ratio);
	hp_->SetFillColorAndOpacity(hp_color);
}

float UCombatResultBlock::GetHPPercent()
{
	return hp_->GetPercent();
}

void UCombatResultBlock::SetHPOpacity(float opacity)
{
	hp_->SetRenderOpacity(opacity);
}

void UCombatResultBlock::SetDamageDealt(float damage)
{
	deal_text_->SetText(FText::AsNumber(damage));
}

void UCombatResultBlock::NativeConstruct()
{
	Super::NativeConstruct();

	hp_->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
}