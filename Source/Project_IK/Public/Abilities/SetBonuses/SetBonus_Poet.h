/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Header file for Poet Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "Structs/DamageData.h"
#include "SetBonus_Poet.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Poet : public USetBonusBase
{
	GENERATED_BODY()

public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;
	
private:
	UFUNCTION()
	void PoetTriangle();

	UFUNCTION()
	void PoetHexagon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Poet, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASentryGun> sentry_gun_class_;
};
