/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.2.2025
Summary : Header file for manager to control TimeDilationManager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeDilationManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UTimeDilationManager : public UObject
{
	GENERATED_BODY()
public:
	UTimeDilationManager();

	UFUNCTION()
	void SetGlobalTimeDilation(UObject* world, float time_dilation);
	UFUNCTION()
	float GetGlobalTimeDilation(UObject* world) const;
	
	UFUNCTION()
	void SlowGlobalTimeDilation(UObject* world);
	UFUNCTION()
	void RestoreGlobalTimeDilation(UObject* world);

	static constexpr float SLOW_SPEED = 0.25f;

private:
	UPROPERTY()
	float last_time_dilation_;
};
