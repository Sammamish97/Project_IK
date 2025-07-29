/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for the Rund Adn Gun Buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_RunAndGun.generated.h"

UCLASS()
class PROJECT_IK_API UBF_RunAndGun : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

private:
	UFUNCTION()
	void OnReposition();
};
