/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.02.2025
Summary : Source file for Cost UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Combat/CostUI.h"
#include "Components/TextBlock.h"
#include "Components/EnergySystemComponent.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameState.h"

void UCostUI::NativeConstruct()
{
	Super::NativeConstruct();
	energy_system_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()))->GetEnergySystemComponent();
}

void UCostUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (energy_system_cache_)
	{
		cost_text_->SetText(FText::AsNumber(static_cast<int>(energy_system_cache_->GetEnergy())));
		image_->GetDynamicMaterial()->SetScalarParameterValue("progress", FMath::Max(energy_system_cache_->GetEnergyRatio() - 0.0999f, 0.f));
	}
}