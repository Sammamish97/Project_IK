/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Header file for a global buff that applies to a hero that has been dead.

Licensed under the MIT Lice	nse.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_Deathbound.generated.h"

enum class EHeroType : uint8;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGB_Deathbound : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
public:

	bool IsBuffValidOnTarget(UObject* buff_target) override;
	void ApplyBuff(UObject* buff_target) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHeroType target_hero_type_;
};
