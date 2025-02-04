/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for Fixed damage reduce equipment skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EquipmentSkillBase.h"
#include "FixedDmgReduce.generated.h"

UCLASS()
class PROJECT_IK_API AFixedDmgReduce : public AEquipmentSkillBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFixedDmgReduce();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void InitEquipmentSkill(AActor* hero_ref) override;
	UFUNCTION()
	virtual FDamageData OnEquipmentSkill(FDamageData dmg_data) override;
};
