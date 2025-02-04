/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.4.2025
Summary : Source file for Equipment Skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EquipmentSkills/EquipmentSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ArmorManager.h"
#include "WorldSettings/IKGameInstance.h"


// Sets default values
AEquipmentSkillBase::AEquipmentSkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEquipmentSkillBase::BeginPlay()
{
	Super::BeginPlay();
	armor_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetArmorManager();
}

void AEquipmentSkillBase::InitEquipmentSkill(AActor* hero_ref)
{
	hero_cache_ = Cast<AHeroBase>(hero_ref);
}

FDamageData AEquipmentSkillBase::OnEquipmentSkill(FDamageData dmg_data)
{
	return dmg_data;
}

void AEquipmentSkillBase::ClearEquipmentSkill()
{
	if (hero_cache_->hero_dmg_event_map_[bound_target_].IsBound())
	{
		hero_cache_->hero_dmg_event_map_[bound_target_].Unbind();
	}
}

// Called every frame
void AEquipmentSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

