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

class ABullet;
class UNiagaraSystem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class PROJECT_IK_API UBulletOnHitEffectComponent : public UActorComponent, public IBulletOnHit
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target, const FHitResult& hit_result) ;
	virtual void ApplyEffect(ABullet* bullet_actor) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> on_hit_material_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> on_hit_effect_;
};
