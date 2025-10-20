/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.16.2025
Summary : Source file for the subsystem for random number generator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/RandomNumberGeneratorSubsystem.h"

FRandomStream URandomNumberGeneratorSubsystem::rng_;

void URandomNumberGeneratorSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

URandomNumberGeneratorSubsystem* URandomNumberGeneratorSubsystem::Get(UWorld* world)
{
	return world->GetGameInstance()->GetSubsystem<URandomNumberGeneratorSubsystem>();
}

FRandomStream& URandomNumberGeneratorSubsystem::GetRNG(UWorld* world)
{
	return Get(world)->rng_;
}

bool URandomNumberGeneratorSubsystem::RandBool() const
{
	return rng_.RandRange(0, 1) == 1;;
}

FVector URandomNumberGeneratorSubsystem::VRand() const
{
	const float cos_theta = rng_.FRandRange(-1.f, 1.f);
	const float phi = rng_.FRandRange(0.f, 2.f * PI);
	const float sin_theta = FMath::Sqrt(1.f - cos_theta * cos_theta);
	return FVector(sin_theta * FMath::Cos(phi), sin_theta * FMath::Sin(phi), cos_theta);
}
