/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for Dagger Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "SetBonusBase.h"
#include "SetBonus_Dagger.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Dagger : public USetBonusBase
{
	GENERATED_BODY()

public:
	USetBonus_Dagger();
	
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;

private:
	UFUNCTION()
	void TriangleReloadCritRateBuff();
	UFUNCTION()
	void HexagonBonus();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rune, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UObjectPoolComponent> bullet_pool_;

	UPROPERTY()
	FTimerHandle bullet_timer_handle_;
};
