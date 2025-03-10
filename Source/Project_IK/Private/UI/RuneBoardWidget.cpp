/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RuneBoardWidget.h"

#include "UI/RuneSlotWidget.h"

bool URuneBoardWidget::Initialize()
{
	Super::Initialize();
	slot_array_.Add(slot_0_);
	slot_array_.Add(slot_1_);
	slot_array_.Add(slot_2_);
	slot_array_.Add(slot_3_);
	slot_array_.Add(slot_4_);
	slot_array_.Add(slot_5_);
	for (int i = 0; i < 6; ++i)
	{
		slot_array_[i]->SetSlotNum(i);
	}
	return true;
}
