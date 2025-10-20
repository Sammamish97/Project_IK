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
class UBuffHandler;

UCLASS()
class PROJECT_IK_API USetBonus_Chariot : public USetBonusBase
{
	GENERATED_BODY()
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

private:
	UFUNCTION()
	void GetShield();

	UFUNCTION()
	void GetShieldAndLifeSteal();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> edge_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> edge_buff_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> hexagon_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> hexagon_buff_;
};
