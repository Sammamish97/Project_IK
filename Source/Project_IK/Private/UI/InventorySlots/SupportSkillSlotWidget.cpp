/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.4.2025
Summary : Header file for Support skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventorySlots/SupportSkillSlotWidget.h"

USupportSkillDataAsset* USupportSkillSlotWidget::GetStoredSupportSkillData()
{
	return support_skill_data_cache_;
}

void USupportSkillSlotWidget::SetSupportSkillSlotData(USupportSkillDataAsset* support_skill_data)
{
	support_skill_data_cache_ = support_skill_data;
}
