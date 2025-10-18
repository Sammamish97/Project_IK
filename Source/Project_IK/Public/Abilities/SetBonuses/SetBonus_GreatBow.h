/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.21.2025
Summary : Header file for the GreatBow Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "Structs/DamageData.h"
#include "SetBonus_GreatBow.generated.h"

class UBulletDeathBlowEffectComponent;
class UBuffHandler;

UCLASS()
class PROJECT_IK_API USetBonus_GreatBow : public USetBonusBase
{
	GENERATED_BODY()
	
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

	UFUNCTION()
	void TriangleReloadCoolDownBonus();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UBulletDeathBlowEffectComponent> effect_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData")
	TSubclassOf<UBuffHandler> edge_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> edge_buff_;

private:
	float active_cooldown_amount_ = 3.f;
};