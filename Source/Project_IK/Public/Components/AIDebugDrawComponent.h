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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	void InitAIController(AAIController* controller);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool is_melee_;
	class AUnit* unit_cache_;
	class UCharacterStatComponent* char_stat_cache_;
	class UWeaponMechanics* weapon_mechanics_cache_;
	class AMeleeAIController* ai_controller_cache_;
};
