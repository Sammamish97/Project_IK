/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Header file for Quake Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "Structs/DamageData.h"
#include "SetBonus_Quake.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Quake : public USetBonusBase
{
	GENERATED_BODY()
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;
	
private:
	UFUNCTION()
	void TriangleAttackSpeedBuff();

	UFUNCTION()
	void HexagonSkillEcho();

private:
	float triangle_buff_duration_ = 3.f;
	float hexagon_effect_cooldown = 15.f;
	FTimerHandle skill_echo_timer_handle_;
};
