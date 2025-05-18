/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.09.2025
Summary : Source file for post process volume for combat level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKPostProcessVolume.h"


namespace
{
    static constexpr float lerp_step = 0.01f;
    static constexpr float lerp_max_value = 1.f;

    static constexpr float thunderstorm_min_brightness = 3.f;
    static constexpr float thunderstorm_max_brightness = 3.f;
    static constexpr float thunderstorm_vigette_intensity = 0.5f;
    static constexpr float thunderstorm_temp = 6000.f;

    // Set by 0.f, event though Unreal default value is -10.
    // Because Unreal prepared to users design too dark scene, our scene does not though. Thus, make it 0.
    static constexpr float default_min_brightness = 0.f;
    static constexpr float default_max_brightness = 20.f;
    static constexpr float default_vignette_intensity = 0.4f;
    static constexpr float default_white_temp = 6500.f;
}

void AIKPostProcessVolume::BeginThunderStorm()
{
    bUnbound = true; // Ensure it's global
    GetWorld()->GetTimerManager().SetTimer(lerp_handle_, this, &AIKPostProcessVolume::LerpToThunderstorm, lerp_step, true);
    lerp_alpha_ = 0.f;
}

void AIKPostProcessVolume::EndThunderStorm()
{
    GetWorld()->GetTimerManager().SetTimer(lerp_handle_, this, &AIKPostProcessVolume::LerpToClear, lerp_step, true);
    lerp_alpha_ = 0.f;
}

void AIKPostProcessVolume::LerpToThunderstorm()
{
    lerp_alpha_ += lerp_step;
    if (lerp_alpha_ >= lerp_max_value)
    {
        lerp_alpha_ = lerp_max_value;
        GetWorld()->GetTimerManager().ClearTimer(lerp_handle_);
    }

    // Lerp settings
    Settings.AutoExposureMinBrightness = 
        FMath::Lerp(default_min_brightness, thunderstorm_min_brightness, lerp_alpha_);
    Settings.AutoExposureMaxBrightness = 
        FMath::Lerp(default_max_brightness, thunderstorm_max_brightness, lerp_alpha_);
    Settings.VignetteIntensity = 
        FMath::Lerp(default_vignette_intensity, thunderstorm_vigette_intensity, lerp_alpha_);
    Settings.WhiteTemp = 
        FMath::Lerp(default_white_temp, thunderstorm_temp, lerp_alpha_);

    // Override switches
    Settings.bOverride_AutoExposureMinBrightness = true;
    Settings.bOverride_AutoExposureMaxBrightness = true;
    Settings.bOverride_VignetteIntensity = true;
    Settings.bOverride_WhiteTemp = true;
}

void AIKPostProcessVolume::LerpToClear()
{
    lerp_alpha_ += lerp_step;
    if (lerp_alpha_ >= lerp_max_value)
    {
        lerp_alpha_ = lerp_max_value;
        GetWorld()->GetTimerManager().ClearTimer(lerp_handle_);
    }

    // Lerp settings
    Settings.AutoExposureMinBrightness = 
        FMath::Lerp(thunderstorm_min_brightness, default_min_brightness, lerp_alpha_);
    Settings.AutoExposureMaxBrightness = 
        FMath::Lerp(thunderstorm_max_brightness, default_max_brightness, lerp_alpha_);
    Settings.VignetteIntensity = FMath::Lerp(thunderstorm_vigette_intensity, default_vignette_intensity, lerp_alpha_);
    Settings.WhiteTemp = FMath::Lerp(thunderstorm_temp, default_white_temp, lerp_alpha_);

    // Override switches
    Settings.bOverride_AutoExposureMinBrightness = false;
    Settings.bOverride_AutoExposureMaxBrightness = false;
    Settings.bOverride_VignetteIntensity = false;
    Settings.bOverride_WhiteTemp = false;
}