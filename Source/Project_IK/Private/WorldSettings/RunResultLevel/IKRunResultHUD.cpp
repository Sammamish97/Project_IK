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

void AIKRunResultHUD::StartRunResultSequence()
{
	if (run_result_manager_)
	{
		run_result_manager_->StartRunResultSequence();
	}
}

void AIKRunResultHUD::SwitchUIByState(ERunResultState state)
{
	if (run_result_manager_)
	{
		run_result_manager_->SwitchUIByState(state);
	}
}

void AIKRunResultHUD::BeginPlay()
{
	Super::BeginPlay();

	if (run_result_manager_class_)
	{
		run_result_manager_ = NewObject<URunResultManager>(this, run_result_manager_class_);
	}
	StartRunResultSequence();
}
