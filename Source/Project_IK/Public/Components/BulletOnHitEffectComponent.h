/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Header file for Bullet On Hit Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/BulletOnHit.h"
#include "BulletOnHitEffectComponent.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract)
class PROJECT_IK_API UBulletOnHitEffectComponent : public UActorComponent, public IBulletOnHit
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void OnHit(AActor* target) override;

protected:
	UPROPERTY()
	TSubclassOf<AActor> target_class_;

	UPROPERTY()
	TObjectPtr<AActor> shooter_ = nullptr;
};
