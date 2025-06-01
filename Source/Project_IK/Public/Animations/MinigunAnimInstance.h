/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Header file for the minigun anim instance.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MinigunAnimInstance.generated.h"
UENUM(BlueprintType)
enum class EMinigunAnimState : uint8
{
	Idle,
	PreHeating,
	OnFire,
	Cooling
};

UCLASS(Blueprintable)
class PROJECT_IK_API UMinigunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void SetMinigunState(EMinigunAnimState new_state);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta = (AllowPrivateAccess=true))
	EMinigunAnimState minigun_state_;
};
