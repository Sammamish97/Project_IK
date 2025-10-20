/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.31.2025
Summary : Source file for HUD class used in RunResultLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/RunResultLevel/IKRunResultHUD.h"

#include "Managers/RunResultManager.h"

#include "UI/RunRewardWidget.h"
#include "Subsystems/LevelTransitionSubsystem.h"

FReply AIKRunResultHUD::HandleKeyboardAction(const FKeyEvent& InKeyEvent)
{
	return run_reward_ui_->NativeOnKeyDown(run_reward_ui_->GetCachedGeometry(), InKeyEvent);
}

void AIKRunResultHUD::BeginPlay()
{
	Super::BeginPlay();


	if (run_reward_ui_class_)
	{
		run_reward_ui_ = CreateWidget<URunRewardWidget>(GetWorld(), run_reward_ui_class_);
		if (run_reward_ui_)
		{
			run_reward_ui_->AddToViewport();
			run_reward_ui_->SetOnConfirm([&]()
				{
					GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenLevel(GetWorld(), ELevelState::Ending);
				});
		}
	}
}
