/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.13.2025
Summary : Header file for perk effects base class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PerkEffectBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UPerkEffectBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void ApplyEffect() PURE_VIRTUAL(UPerkEffectBase::ApplyEffect, );
	virtual void RemoveEffect() PURE_VIRTUAL(UPerkEffectBase::RemoveEffect, );
protected:

};
