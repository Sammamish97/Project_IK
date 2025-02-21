// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OopartBase.h"
#include "AttackSpeedBoostOopart.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API AAttackSpeedBoostOopart : public AOopartBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackSpeedBoostOopart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AttackSpeedBuff();

private:
	FTimerHandle cool_time_handle_;
	float cool_down_;
	float duration_;
	float boost_amount_;
};
