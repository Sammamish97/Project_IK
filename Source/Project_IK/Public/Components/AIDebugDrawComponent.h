/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.6.2025
Summary : Header file for AIDebugDrawComponent.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIDebugDrawComponent.generated.h"


class AAIController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UAIDebugDrawComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIDebugDrawComponent();
	void SetActivated(bool activated);
	void SetActivated(float activated_time);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	void InitAIController(AAIController* controller);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<class AUnit> unit_cache_;

	UPROPERTY()
	TObjectPtr<class UCharacterStatComponent> char_stat_cache_;
	
	UPROPERTY()
	TObjectPtr<class UWeaponMechanics> weapon_mechanics_cache_;
	
	UPROPERTY()
	TObjectPtr<class AMeleeAIController> ai_controller_cache_;

	bool activated_ = false;
	float activated_time_ = -1.f;
	float delta_time_ = 0.f;
};
