/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.02.2025
Summary : Source file for Cost UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/CostUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/EnergySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameState.h"

void UCostUI::NativeConstruct()
{
	Super::NativeConstruct();
	progress_bar_->SetPercent(0.f);
	energy_system_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()))->GetEnergySystemComponent();
}

void UCostUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (progress_bar_ && energy_system_cache_)
	{
		progress_bar_->SetPercent(energy_system_cache_->GetEnergyRatio());
		cost_text_->SetText(FText::AsNumber(static_cast<int>(energy_system_cache_->GetEnergy())));
	}
}