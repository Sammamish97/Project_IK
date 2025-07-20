/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.14.2025
Summary : Header file for perk effects that apply GlobalBuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "PE_ApplyGlobalBuff.generated.h"

enum class EGlobalBuffType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_ApplyGlobalBuff : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGlobalBuffType global_buff_type_;
};
