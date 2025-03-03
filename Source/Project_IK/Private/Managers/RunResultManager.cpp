/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Source file of a manager that handles UI controls after runs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RunResultManager.h"

// Need to call CreateWidget function
#include "Blueprint/UserWidget.h"
#include "UI/ToMainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

void URunResultManager::StartRunResultSequence()
{
	if (main_menu_ui_class_)
	{
		
		main_menu_ui_ = CreateWidget<UToMainMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), main_menu_ui_class_);
		if (main_menu_ui_)
		{
			main_menu_ui_->AddToViewport();
		}
	}
}
