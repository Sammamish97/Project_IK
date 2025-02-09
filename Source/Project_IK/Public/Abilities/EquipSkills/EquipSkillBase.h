/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/EquipSkill.h"
#include "EquipSkillBase.generated.h"

UCLASS()
class PROJECT_IK_API UEquipSkillBase : public UObject, public IEquipSkill
{
	GENERATED_BODY()
public:
	UEquipSkillBase() = default;

public:
	virtual FDamageData OnEquipmentSkill(FDamageData dmg_data) override;
	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	class AHeroBase* hero_cache_;
	EHeroEvent bound_target_;
	class UArmorManager* armor_manager_cache_;
};
