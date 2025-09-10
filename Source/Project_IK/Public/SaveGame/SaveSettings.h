/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.09.2025
Summary : Header file for SaveGame that saves game settings.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/BaseSaveGame.h"
#include "SaveSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API USaveSettings : public UBaseSaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	float master_volume_ = 1.f;
	UPROPERTY(VisibleAnywhere)
	float music_volume_ = 1.f;
	UPROPERTY(VisibleAnywhere)
	float sfx_volume_ = 1.f;
};
