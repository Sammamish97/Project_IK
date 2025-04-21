/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Header file for the Chariot Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "SetBonusBase.h"
#include "SetBonus_Chariot.generated.h"

UCLASS()
class PROJECT_IK_API USetBonus_Chariot : public USetBonusBase
{
	GENERATED_BODY()
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

private:
	FDamageData GetShield(FDamageData dmg_data);
	FDamageData GetShieldAndLifeSteal(FDamageData dmg_data);


private:
	float shield_duration_ = 3.f;
	float life_steal_percentage = 10.f;
};
