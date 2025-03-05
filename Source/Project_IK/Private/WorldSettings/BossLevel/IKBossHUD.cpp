/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Source file for HUD in BossLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/BossLevel/IKBossHUD.h"

#include "Managers/RunResultManager.h"

void AIKBossHUD::StartRunResultSequence()
{
	if (run_result_manager_)
	{
		run_result_manager_->StartRunResultSequence();
	}
}

void AIKBossHUD::BeginPlay()
{
	if (run_result_manager_class_)
	{
		run_result_manager_ = NewObject<URunResultManager>(GetOwningPlayerController(), run_result_manager_class_);
	}
	StartRunResultSequence();
}
