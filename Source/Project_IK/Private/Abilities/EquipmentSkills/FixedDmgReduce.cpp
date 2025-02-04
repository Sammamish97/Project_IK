/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for Fixed damage reduce equipment skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EquipmentSkills/FixedDmgReduce.h"

#include "Characters/HeroBase.h"


// Sets default values
AFixedDmgReduce::AFixedDmgReduce()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFixedDmgReduce::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFixedDmgReduce::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	bound_target_ = EHeroEvent::OnHitAfterCalc;
	hero_cache_->hero_dmg_event_map_.FindOrAdd(bound_target_).BindUObject(this, &AFixedDmgReduce::OnEquipmentSkill);
}

FDamageData AFixedDmgReduce::OnEquipmentSkill(FDamageData dmg_data)
{
	dmg_data.damage -= 3;
	return dmg_data;
}

