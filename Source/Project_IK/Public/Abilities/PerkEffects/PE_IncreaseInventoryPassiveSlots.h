/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.21.2025
Summary : Header file for perk effects that increase inventory_passive_skill_unlocked_slots_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "PE_IncreaseInventoryPassiveSlots.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_IncreaseInventoryPassiveSlots : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 new_inventory_passive_skill_unlocked_slots_ = 0;
};
