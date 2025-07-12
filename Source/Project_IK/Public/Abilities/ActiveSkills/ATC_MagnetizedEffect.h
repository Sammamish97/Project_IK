/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.18.2025
Summary : Header file for Magnetized Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ATC_MagnetizedEffect.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UATC_MagnetizedEffect : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void IncreaseStack();
	void OnMaxStack();
	void OnDurationExpired();

private:
	int32 stack_ = 1;
	const int32 max_stack_ = 3;
	float duration_ = 0.f;
	FTimerHandle duration_timer_handle_;
};
