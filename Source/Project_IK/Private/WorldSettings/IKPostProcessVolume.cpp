/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.09.2025
Summary : Source file for post process volume for combat level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKPostProcessVolume.h"

void AIKPostProcessVolume::BeginThunderStorm()
{
	bUnbound = true; // Ensure it's global
	GetWorld()->GetTimerManager().SetTimer(lerp_handle_, this, &AIKPostProcessVolume::LerpToThunderstorm, lerp_step_, true);
	lerp_alpha_ = 0.f;

	Settings.AutoExposureSpeedUp = default_speed_up;
	Settings.AutoExposureSpeedDown = default_speed_down;

	is_thunderstorm_working_ = true;
}

void AIKPostProcessVolume::EndThunderStorm()
{
	GetWorld()->GetTimerManager().SetTimer(lerp_handle_, this, &AIKPostProcessVolume::LerpToClear, lerp_step_, true);
	lerp_alpha_ = 0.f;

	Settings.AutoExposureSpeedUp = default_speed_up;
	Settings.AutoExposureSpeedDown = default_speed_down;
}

void AIKPostProcessVolume::SetDarkening(bool is_enabled)
{
	// Ignore darkening effects when thunder storm effect is working.
	if (is_thunderstorm_working_)
	{
		return;
	}

	if (is_enabled)
	{
		Settings.AutoExposureMinBrightness =
			darkening_min_brightness;
		Settings.AutoExposureMaxBrightness =
			darkening_max_brightness;
		Settings.VignetteIntensity =
			thunderstorm_vigette_intensity_;
		Settings.WhiteTemp =
			thunderstorm_temp_;
		Settings.AutoExposureSpeedUp = darkening_speed;
		Settings.AutoExposureSpeedDown = darkening_speed;
	}
	else
	{
		Settings.AutoExposureMinBrightness =
			default_min_brightness_;
		Settings.AutoExposureMaxBrightness =
			default_max_brightness_;
		Settings.VignetteIntensity = default_vignette_intensity_;
		Settings.WhiteTemp = default_white_temp_;
		Settings.AutoExposureSpeedUp = darkening_speed;
		Settings.AutoExposureSpeedDown = darkening_speed;
	}
}

void AIKPostProcessVolume::BeginPlay()
{
	Settings.bOverride_AutoExposureMinBrightness = true;
	Settings.bOverride_AutoExposureMaxBrightness = true;
	Settings.bOverride_VignetteIntensity = true;
	Settings.bOverride_WhiteTemp = true;
	Settings.bOverride_AutoExposureSpeedUp = true;
	Settings.bOverride_AutoExposureSpeedDown = true;

}

void AIKPostProcessVolume::LerpToThunderstorm()
{
	lerp_alpha_ += lerp_step_;
	if (lerp_alpha_ >= lerp_max_value_)
	{
		lerp_alpha_ = lerp_max_value_;
		GetWorld()->GetTimerManager().ClearTimer(lerp_handle_);
	}

	// Lerp settings
	Settings.AutoExposureMinBrightness =
		FMath::Lerp(default_min_brightness_, thunderstorm_min_brightness_, lerp_alpha_);
	Settings.AutoExposureMaxBrightness =
		FMath::Lerp(default_max_brightness_, thunderstorm_max_brightness_, lerp_alpha_);
	Settings.VignetteIntensity =
		FMath::Lerp(default_vignette_intensity_, thunderstorm_vigette_intensity_, lerp_alpha_);
	Settings.WhiteTemp =
		FMath::Lerp(default_white_temp_, thunderstorm_temp_, lerp_alpha_);
}

void AIKPostProcessVolume::LerpToClear()
{
	lerp_alpha_ += lerp_step_;
	if (lerp_alpha_ >= lerp_max_value_)
	{
		lerp_alpha_ = lerp_max_value_;
		GetWorld()->GetTimerManager().ClearTimer(lerp_handle_);

		is_thunderstorm_working_ = false;
	}

	// Lerp settings
	Settings.AutoExposureMinBrightness =
		FMath::Lerp(thunderstorm_min_brightness_, default_min_brightness_, lerp_alpha_);
	Settings.AutoExposureMaxBrightness =
		FMath::Lerp(thunderstorm_max_brightness_, default_max_brightness_, lerp_alpha_);
	Settings.VignetteIntensity = FMath::Lerp(thunderstorm_vigette_intensity_, default_vignette_intensity_, lerp_alpha_);
	Settings.WhiteTemp = FMath::Lerp(thunderstorm_temp_, default_white_temp_, lerp_alpha_);
}