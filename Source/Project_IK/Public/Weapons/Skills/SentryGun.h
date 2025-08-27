/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.25.2025
Summary : Header file for Sentry Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/Unit.h"
#include "SentryGun.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API ASentryGun : public AUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASentryGun();
	
	virtual void InitSentryGun(bool is_upgraded, float skill_power);
	virtual void BeginFire(TWeakObjectPtr<AActor> target);
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void OnFire(TWeakObjectPtr<AActor> target);

	UFUNCTION()
	virtual void StopFire();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	float hit_points_scaling_factor_ = 0.8f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	float dmg_scaling_factor_ = 0.8f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UObjectPoolComponent> bullet_pool_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> muzzle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AUnit> target_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SentryGun", meta = (AllowPrivateAccess = "true"))
	FTimerHandle fire_timer_handle_;
};
