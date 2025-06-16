/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Source file for energy system.
					It will be used as a resource to invoke characters skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Components/EnergySystemComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UEnergySystemComponent::UEnergySystemComponent()
	: Super::UActorComponent(), energy_(10.f), regen_rate_(20.f), max_energy_(100.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEnergySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEnergyChanged.Clear();
}


// Called every frame
void UEnergySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RegenEnergy(DeltaTime);
}

float UEnergySystemComponent::GetEnergy() const noexcept
{
	return energy_;
}

float UEnergySystemComponent::GetEnergyRatio() const noexcept
{
	return energy_ / max_energy_;
}

float UEnergySystemComponent::GetRegenRate() const noexcept
{
	return regen_rate_;
}

float UEnergySystemComponent::GetMaxEnergy() const noexcept
{
	return max_energy_;
}

void UEnergySystemComponent::RegenEnergy(float DeltaTime)
{
	float prev_energy = energy_;
	energy_ = FMath::Min(energy_ + DeltaTime * regen_rate_, max_energy_);

	if (prev_energy != energy_)
	{
		OnEnergyChanged.Broadcast(energy_, max_energy_);
	}
}

bool UEnergySystemComponent::UseEnergy(float amount)
{
	// When the parameter is negative,
	if (amount < 0.f)
	{
		return false;
	}

	// When usage is bigger than stored energy,
	if (energy_ < amount)
	{
		return false;
	}

	energy_ -= amount;
	OnEnergyChanged.Broadcast(energy_, max_energy_);

	return true;
}

