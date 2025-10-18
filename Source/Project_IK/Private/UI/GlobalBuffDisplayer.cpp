/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.27.2024
Summary : Source file for UI that displays global buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/GlobalBuffDisplayer.h"

#include "Components/UniformGridPanel.h"

#include "Components/Image.h"

#include "Subsystems/GlobalBuffSubsystem.h"
#include "Blueprint/WidgetTree.h"

#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"

void UGlobalBuffDisplayer::NativeConstruct()
{
	UGlobalBuffSubsystem* global_buff_subsystem = GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	TArray<FGlobalBuffData> buffs = global_buff_subsystem->GetBuffs();

	// Naively implement for sake of implementation of displaying everlasting buffs rapidly.
	// @@ Improvements: design and improve the way displaying everlasting buffs.

	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (instance)
	{
		UDataTableManager* data_table_manager = instance->GetDataTableManager();

		TSet<EGlobalBuffType> everlasting_buff_types = global_buff_subsystem->GetEverlastingBuffTypes();
		for (EGlobalBuffType type : everlasting_buff_types)
		{
			buffs.Add(data_table_manager->GetGlobalBuffData(type));
		}
	}

	int32 buff_amount = buffs.Num();
	for (size_t i = 0; i < buff_amount; i++)
	{
		UImage* image = WidgetTree->ConstructWidget<UImage>();
		FSlateBrush brush = image->GetBrush();
		
		brush.SetResourceObject(buffs[i].thumbnail_);
		brush.SetImageSize(FVector2D(128.f, 128.f));
		image->SetBrush(brush);
		
		global_buff_widget_holder_->AddChildToUniformGrid(image, buff_amount / grid_column_, buff_amount % grid_column_);
	}
}

void UGlobalBuffDisplayer::NativeDestruct()
{
}
