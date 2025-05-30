/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Header file for the Auto gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "AutoGun.generated.h"

UCLASS(ABstract)
class PROJECT_IK_API AAutoGun : public AGunBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginFire(AActor* target) override;
	void OnFire(AActor* target, float attack_speed);
};
