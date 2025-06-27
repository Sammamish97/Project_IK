/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.05.2025
Summary : Source file for HP UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/SegmentedHPUI.h"
#include "Components/Image.h"

void USegmentedHPUI::UpdateWidget(float cur_hp, float cur_shield)
{
	Super::UpdateWidget(cur_hp, cur_shield);
	SetMaterialSegmentWidth();
}

void USegmentedHPUI::SetMaterialSegmentWidth() const
{
	float segment_width = 100.f / (cur_max_hp_ / segment_amount);
	separator_->GetDynamicMaterial()->SetScalarParameterValue("segment_width", segment_width);
}
