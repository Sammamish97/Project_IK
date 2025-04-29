/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Header file for Bullet Chain Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BulletOnHitEffectComponent.h"
#include "BulletChainEffectComponent.generated.h"
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UBulletChainEffectComponent : public UBulletOnHitEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target) override;

private:
	int32 chain_amount_ = 3;
	float chain_radius_ = 1000.f;
};
