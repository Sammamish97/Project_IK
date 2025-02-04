/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for Equipment Skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/EquipmentSkill.h"
#include "Managers/EnumCluster.h"
#include "EquipmentSkillBase.generated.h"

UCLASS()
class PROJECT_IK_API AEquipmentSkillBase : public AActor, public IEquipmentSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquipmentSkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual FDamageData OnEquipmentSkill(FDamageData dmg_data) override;
	virtual void InitEquipmentSkill(AActor* hero_ref) override;
	virtual void ClearEquipmentSkill() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	class AHeroBase* hero_cache_;
	EHeroEvent bound_target_;
	class UArmorManager* armor_manager_cache_;
	//UAudioComponent* audio for skill
	//NiagaraComponent* VFX for skill
};
