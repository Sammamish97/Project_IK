/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Header file for magnetized bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_MagnetizedBullet.generated.h"
class UBulletMagnetizeEffectComponent;

UCLASS()
class PROJECT_IK_API UBF_MagnetizedBullet : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MagnetizedBullet", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBulletMagnetizeEffectComponent> magnetized_on_hit_class_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MagnetizedBullet", meta = (AllowPrivateAccess = "true"))
	float duration_ = 0.f;
	
	FTimerHandle duration_timer_handle_;
};
