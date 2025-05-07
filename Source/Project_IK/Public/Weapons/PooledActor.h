/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.05.2024
Summary : Header file for Pooled Actor which for the Object pool.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API APooledActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledActor();
	bool GetInUse() const;
	virtual void SetInUse(bool in_use);
	virtual void ReturnToPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	float time_to_live_;

	UPROPERTY(Transient)
	bool in_use_;

	UPROPERTY(Transient)
	FTimerHandle timer_handle_;
};
