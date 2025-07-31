/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.29.2025
Summary : Header file for Enemy Soldier A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Enemy_RifleMan.h"
#include "Enemy_Soldier_A.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_Soldier_A : public AEnemy_RifleMan
{
	GENERATED_BODY()

public:
	virtual void OnEnterBattleOnce() override;
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void GetBonusPower();
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float preheat_duration_ = 5.f;

	UPROPERTY()
	FTimerHandle preheat_timer_;

	UPROPERTY(EditDefaultsOnly, category = "Unit", meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> buff_;
};
