/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.01.2025
Summary : Header file for a global buff that remove negative events.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_EventReconEventBuff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_EventReconEventBuff : public UGlobalBuffLogicBase
{
	GENERATED_BODY()

public:
	virtual void OnBuffExpired() override;
	
};
