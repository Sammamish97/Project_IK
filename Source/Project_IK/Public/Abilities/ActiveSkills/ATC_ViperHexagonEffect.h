/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.22.2025
Summary : Header file for viper hexagon Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ATC_ViperHexagonEffect.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UATC_ViperHexagonEffect : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UATC_ViperHexagonEffect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void IncreaseStack();
	void OnMaxStack();
	void OnDurationExpired();
	
private:
	int32 stack_ = 1;
	const int32 max_stack_ = 3;
	float effect_duration_ = 0.f;
	FTimerHandle duration_timer_handle_;
};
