/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Level HUD class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/EventLevel/IKEventLevelHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EventManager.h"
#include "Components/Button.h"
#include "UI/EventWidget.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"

void AIKEventLevelHUD::BeginPlay()
{
	Super::BeginPlay();
	if(event_widget_class_)
	{
		event_widget_ = CreateWidget<UEventWidget>(GetWorld(), event_widget_class_);
		if(event_widget_)
		{
			auto ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			auto event_manager = ik_instance->GetEventManager();
			if(ik_instance)
			{
				FEventData cur_event_data = event_manager->GetRandomEventData();
				event_widget_->InitEventWidget(cur_event_data);
				event_widget_->AddToViewport();
				// BindEventResult must be bound before binding AfterPickOption
				event_manager->BindEventResult(cur_event_data, event_widget_);
				event_widget_->button_1_->OnClicked.AddDynamic(this, &AIKEventLevelHUD::AfterPickOption);
				event_widget_->button_2_->OnClicked.AddDynamic(this, &AIKEventLevelHUD::AfterPickOption);
				event_widget_->button_3_->OnClicked.AddDynamic(this, &AIKEventLevelHUD::AfterPickOption);
				event_widget_->button_4_->OnClicked.AddDynamic(this, &AIKEventLevelHUD::AfterPickOption);
			}
		}
	}
}

void AIKEventLevelHUD::AfterPickOption()
{
	GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
}
