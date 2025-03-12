/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Header file for a virtual super class that contains logic of a global buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalBuffLogicBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_IK_API UGlobalBuffLogicBase : public UObject
{
	GENERATED_BODY()
public:
	// A function that returns true if the parameter is expected data such as AActor*, UIKGameMode*
	virtual bool IsBuffValidOnTarget(UObject* buff_target);

	// A function that contains real logic of buffs or triggers applying buffs.
	virtual void ApplyBuff(UObject* buff_target);

protected:

};
