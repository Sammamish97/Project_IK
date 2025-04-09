/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.08.2025
Summary : Header file for equipment reward widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/EquipmentRewardWidget.h"

void UEquipmentRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	candidates_items_widgets_.Empty();
}
