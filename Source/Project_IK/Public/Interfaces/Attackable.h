/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.10.2025
Summary : Header file for Attackable interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "UObject/Interface.h"
#include "Attackable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackable : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IAttackable
{	
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Attack(AActor* target) = 0;
};
