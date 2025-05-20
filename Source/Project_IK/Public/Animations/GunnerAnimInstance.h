/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.8.2025
Summary : Header file of Anim instance of Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Managers/EnumCluster.h"
#include "GunnerAnimInstance.generated.h"
UCLASS()
class PROJECT_IK_API UGunnerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<class AUnit> gunner_ptr_;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<class UCharacterMovementComponent> movement_component_ptr_;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
    EWeaponAnimationType anim_type_;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
    float speed_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float pitch_;
};
