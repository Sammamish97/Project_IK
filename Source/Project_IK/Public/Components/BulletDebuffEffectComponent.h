/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for the Debuff Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "BulletOnHitEffectComponent.h"
#include "BulletDebuffEffectComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UBulletDebuffEffectComponent : public UBulletOnHitEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target) override;

private:
	float debuff_amount_ = -20.f;
	float debuff_duration_ = 3.f;
};
