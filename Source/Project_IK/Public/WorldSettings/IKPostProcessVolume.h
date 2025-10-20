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
UCLASS(Blueprintable)
class PROJECT_IK_API AIKPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()

public:
	void BeginThunderStorm();
	void EndThunderStorm();

	void SetDarkening(bool is_enabled);

protected:
    virtual void BeginPlay() override;

	void LerpToThunderstorm();
	void LerpToClear();

	FTimerHandle lerp_handle_;
	float lerp_alpha_ = 0.f;


    const float lerp_step_ = 0.01f;
    const float lerp_max_value_ = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float thunderstorm_min_brightness_ = 3.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float thunderstorm_max_brightness_ = 3.f;
    const float thunderstorm_vigette_intensity_ = 0.5f;
    const float thunderstorm_temp_ = 6000.f;

    // Set by 0.f, event though Unreal default value is -10.
    // Because Unreal prepared to users design too dark scene, our scene does not though. Thus, make it 0.
    const float default_min_brightness_ = 0.f;
    const float default_max_brightness_ = 20.f;
    const float default_vignette_intensity_ = 0.4f;
    const float default_white_temp_ = 6500.f;


    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float darkening_min_brightness = 2.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float darkening_max_brightness = 5.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float darkening_speed = 20.f;
    const float default_speed_up = 3.f;
    const float default_speed_down = 1.f;

    bool is_thunderstorm_working_ = false;
};
