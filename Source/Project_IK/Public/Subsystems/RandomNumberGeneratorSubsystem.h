/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.16.2025
Summary : Source file for the subsystem for random number generator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RandomNumberGeneratorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API URandomNumberGeneratorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;

	static URandomNumberGeneratorSubsystem* Get(UWorld* world);
	static FRandomStream& GetRNG(UWorld* world);

	bool RandBool() const;
	FVector VRand() const;
protected:
	static FRandomStream rng_;
};
