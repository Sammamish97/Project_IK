/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.12.2025
Summary : Header file for the Bullet Magnetize Effect On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BulletOnHitEffectComponent.h"
#include "BulletMagnetizeEffectComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UBulletMagnetizeEffectComponent : public UBulletOnHitEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target, const FHitResult& hit_result) override;
	virtual void ApplyEffect(ABullet* bullet_actor) const override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SkillData", meta=(AllowPrivateAccess=true))
	float skill_power_scale_ = 0.8f;
};
