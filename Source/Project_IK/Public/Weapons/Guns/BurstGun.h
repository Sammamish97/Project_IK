/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Header file for the Burst Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "BurstGun.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API ABurstGun : public AGunBase
{
	GENERATED_BODY()

protected:
	virtual void BeginFire(AActor* target) override;
	virtual void OnFire(AActor* target, FDamageData dmg_data, float attack_speed);
	virtual void OnReload() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void FinishBurstCooldown();
	
private:
	UPROPERTY(Transient)
	int32 burst_count_ = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 burst_amount_ = 4;
	
	UPROPERTY(Transient)
	int32 wait_after_burst_ = 1.0f;

	UPROPERTY(Transient)
	FTimerHandle burst_timer_handle_;

	UPROPERTY(Transient)
	bool on_burst_cool_down_ = false;
};