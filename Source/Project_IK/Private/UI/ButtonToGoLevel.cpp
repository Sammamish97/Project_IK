/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.26.2025
Summary : Source file of UI that contains a button to open a map level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ButtonToGoLevel.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Components/Button.h"


void UButtonToGoLevel::SetTargetLevelName(FName target_level_name)
{
	target_level_name_ = target_level_name;
}

FName UButtonToGoLevel::GetTargetLevelName() const
{
	return target_level_name_;
}

void UButtonToGoLevel::NativeConstruct()
{
	opener_button_->OnClicked.AddDynamic(this, &UButtonToGoLevel::OnOpenerButtonClicked);
}

void UButtonToGoLevel::NativeDestruct()
{
	if (opener_button_->OnClicked.IsBound())
	{
		opener_button_->OnClicked.Clear();
	}
}

void UButtonToGoLevel::OnOpenerButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), target_level_name_);
}