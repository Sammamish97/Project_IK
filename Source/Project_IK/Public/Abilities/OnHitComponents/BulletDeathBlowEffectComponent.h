/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.21.2025
Summary : Header file for the Death Blow Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BulletOnHitEffectComponent.h"
#include "BulletDeathBlowEffectComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UBulletDeathBlowEffectComponent : public UBulletOnHitEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target, const FHitResult& hit_result) override;

protected:
	void SpawnBleedingParticle(AActor* target, const FHitResult& hit_result);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> bleeding_particle_;

private:
	float death_blow_percentage_ = 0.5f;
};
