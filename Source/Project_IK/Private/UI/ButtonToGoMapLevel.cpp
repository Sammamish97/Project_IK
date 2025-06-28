/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.26.2025
Summary : Source file of UI that contains a button to open a map level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ButtonToGoMapLevel.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Components/Button.h"


void UButtonToGoMapLevel::NativeConstruct()
{
	map_opener_button_->OnClicked.AddDynamic(this, &UButtonToGoMapLevel::OnMapOpenerButtonClicked);
}

void UButtonToGoMapLevel::NativeDestruct()
{
	if (map_opener_button_->OnClicked.IsBound())
	{
		map_opener_button_->OnClicked.Clear();
	}
}

void UButtonToGoMapLevel::OnMapOpenerButtonClicked()
{
	UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
}