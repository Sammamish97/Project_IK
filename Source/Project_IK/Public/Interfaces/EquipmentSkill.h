/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for equipment skill interface.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/DamageData.h"
#include "EquipmentSkill.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEquipmentSkill : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_IK_API IEquipmentSkill
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InitEquipmentSkill(AActor* hero_ref) = 0;
	virtual FDamageData OnEquipmentSkill(FDamageData dmg_data) = 0;
	virtual void ClearEquipmentSkill() = 0;
};
