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

class UBuffHandler;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API UBulletDebuffEffectComponent : public UBulletOnHitEffectComponent
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target, const FHitResult& hit_result) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> debuff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> debuff_;
};
