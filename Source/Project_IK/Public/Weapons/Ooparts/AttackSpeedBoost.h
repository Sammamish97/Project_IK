// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OopartBase.h"
#include "AttackSpeedBoost.generated.h"

UCLASS()
class PROJECT_IK_API AAttackSpeedBoost : public AOopartBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackSpeedBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float cool_down_;
	float duration_;
	float boost_amount_;
};
