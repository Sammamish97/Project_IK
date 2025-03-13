/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Header file for enemy base. All enemy should inherit this class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Characters/Unit.h"
#include "EnemyBase.generated.h"

UCLASS()
class PROJECT_IK_API AEnemyBase : public AUnit
{
	GENERATED_BODY()
public:
	AEnemyBase();
protected:
	virtual void Die() override;
};
