/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.30.2025
Summary : Header file for Enemy Officer A.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Enemy_Officer.h"
#include "Enemy_Officer_A.generated.h"

class AOfficerShield;

UCLASS()
class PROJECT_IK_API AEnemy_Officer_A : public AEnemy_Officer
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnHPChanged(float ratio);
	void UseForceShield();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AOfficerShield> force_shield_class_;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float shield_hp_threshold_ = 0.9f;

	UPROPERTY(Transient)
	TObjectPtr<AOfficerShield> force_shield_ptr_;
	
	bool use_force_shield_ = false;
};
