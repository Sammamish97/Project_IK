/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.05.2024
Summary : Source file for Pooled Actor which for the Object pool.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/PooledActor.h"

// Sets default values
APooledActor::APooledActor()
	: AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ReturnToPool();
	time_to_live_ = 3.0f;
}

// Called when the game starts or when spawned
void APooledActor::BeginPlay()
{
	Super::BeginPlay();
	ReturnToPool();
}

bool APooledActor::GetInUse() const
{
	return in_use_;
}

void APooledActor::SetInUse(bool in_use)
{
	in_use_ = in_use;
	SetActorEnableCollision(in_use_);
	SetActorTickEnabled(in_use_);
	SetActorHiddenInGame(!in_use_);
	if(in_use_ == true)
	{
		GetWorld()->GetTimerManager().SetTimer(timer_handle_, this, &APooledActor::ReturnToPool, time_to_live_);
	}
}

void APooledActor::ReturnToPool()
{
	SetInUse(false);
}
