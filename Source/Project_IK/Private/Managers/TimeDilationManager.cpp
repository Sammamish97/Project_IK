/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.2.2025
Summary : Source file for manager to control TimeDilationManager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/TimeDilationManager.h"

#include "Kismet/GameplayStatics.h"

UTimeDilationManager::UTimeDilationManager()
	:Super::UObject(), last_time_dilation_(1.f)
{
}

void UTimeDilationManager::SetGlobalTimeDilation(UObject* world, float time_dilation)
{
	if (!FMath::IsNearlyEqual(time_dilation, UGameplayStatics::GetGlobalTimeDilation(world)))
	{
		UGameplayStatics::SetGlobalTimeDilation(world, time_dilation);
	}
}

float UTimeDilationManager::GetGlobalTimeDilation(UObject* world) const
{
	return UGameplayStatics::GetGlobalTimeDilation(world);
}

void UTimeDilationManager::SlowGlobalTimeDilation(UObject* world)
{
	float time_dilation = UGameplayStatics::GetGlobalTimeDilation(world);
	if (!FMath::IsNearlyEqual(time_dilation, last_time_dilation_))
	{
		UGameplayStatics::SetGlobalTimeDilation(world, SLOW_SPEED);
	}
	last_time_dilation_ = time_dilation;
}

void UTimeDilationManager::RestoreGlobalTimeDilation(UObject* world)
{
	if (!FMath::IsNearlyEqual(UGameplayStatics::GetGlobalTimeDilation(world), last_time_dilation_))
	{
		UGameplayStatics::SetGlobalTimeDilation(world, last_time_dilation_);
	}
}
