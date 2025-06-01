/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Header file for the minigun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "Minigun.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AMinigun : public AGunBase
{
	GENERATED_BODY()
public:
	virtual void BeginFire(AActor* target) override;
	void OnFinishPreheat(AActor* target);
	void OnFire(AActor* target);
	void FinishFire() override;

private:
	float pre_heat_time_ = 1.f;
	FTimerHandle pre_heat_timer_;
	bool on_fire_ = false;
};
