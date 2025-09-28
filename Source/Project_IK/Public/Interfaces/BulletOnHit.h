/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.17.2025
Summary : Header file for Bullet On Hit interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BulletOnHit.generated.h"

struct FHitResult;

// This class does not need to be modified.
UINTERFACE()
class UBulletOnHit : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IBulletOnHit
{
	GENERATED_BODY()

public:
	virtual void OnHit(AActor* target, const FHitResult& hit_result) = 0;
};
