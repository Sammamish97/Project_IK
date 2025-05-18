/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.09.2025
Summary : Header file for post process volume for combat level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "IKPostProcessVolume.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
	void BeginThunderStorm();
	void EndThunderStorm();

protected:
	void LerpToThunderstorm();
	void LerpToClear();

	FTimerHandle lerp_handle_;
	float lerp_alpha_ = 0.f;
};
