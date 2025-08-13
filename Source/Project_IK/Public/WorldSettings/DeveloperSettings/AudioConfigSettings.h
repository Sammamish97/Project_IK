/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.12.2025
Summary : Header file for audio configuration settings. It will be used to initialize audio subsystem.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AudioConfigSettings.generated.h"

class UAudioDataAsset;
class USoundMix;

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Audio Config"))
class PROJECT_IK_API UAudioConfigSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UAudioDataAsset> audio_data_asset_;
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<USoundMix> master_mix_;
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<USoundClass> master_channel_;
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<USoundClass> bgm_channel_;
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<USoundClass> sfx_channel_;

	float master_volume_ = 1.f;
	float bgm_volume_ = 1.f;
	float sfx_volume_ = 1.f;
};
