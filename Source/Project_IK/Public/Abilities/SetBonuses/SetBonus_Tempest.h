/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for the Tempest Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "Structs/DamageData.h"
#include "SetBonus_Tempest.generated.h"

UCLASS()
class PROJECT_IK_API USetBonus_Tempest : public USetBonusBase
{
	GENERATED_BODY()
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

private:
	FDamageData TriangleAutoReload(FDamageData DamageData);
	FDamageData HexagonCoolDownBuff(FDamageData DamageData);

private:
	FName cool_down_buff_name = "Tempest_Hexagon";
	int32 cur_buff_stack = 0;
};
