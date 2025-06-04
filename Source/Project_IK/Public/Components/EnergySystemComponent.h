/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Header file for energy system.
					It will be used as a resource to invoke characters skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergySystemComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnergyChanged, float, NewEnergy, float, MaxEnergy);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UEnergySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetEnergy() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetEnergyRatio() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetRegenRate() const noexcept;
	UFUNCTION(BlueprintPure)
	float GetMaxEnergy() const noexcept;
	void RegenEnergy(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Energy")
	bool UseEnergy(float amount);
		
protected:
	UPROPERTY(VisibleAnywhere, Category = "Energy")
	float energy_;

	UPROPERTY(VisibleAnywhere, Category = "Energy")
	float regen_rate_;

	UPROPERTY(VisibleAnywhere, Category = "Energy")
	float max_energy_;

	UPROPERTY(BlueprintAssignable, Category = "Energy")
	FOnEnergyChanged OnEnergyChanged;
};
