/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Environments/Cover.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CharacterStatComponent.h"
// Sets default values
ACover::ACover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	cover_collider_ = CreateDefaultSubobject<UBoxComponent>(FName("cover_collider"));
	cover_position_ = CreateDefaultSubobject<USphereComponent>(FName("cover_position"));
	cover_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("cover_mesh"));
	character_stat_component_ = CreateDefaultSubobject<UCharacterStatComponent>(FName("character_stat"));

	cover_collider_->SetupAttachment(cover_position_);
	cover_collider_->SetMobility(EComponentMobility::Movable);
	
	cover_mesh_->SetupAttachment(cover_collider_);
	cover_mesh_->SetMobility(EComponentMobility::Movable);

	cover_position_->SetMobility(EComponentMobility::Static);
	
	character_stat_component_->Die.AddDynamic(this, &ACover::Die);
	
	SetRootComponent(cover_position_);
}

// Called when the game starts or when spawned
void ACover::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACover::GetDamage(FDamageData data)
{
	character_stat_component_->GetDamage(data);

	// Do not record damages worked on covers...
}

void ACover::Die()
{
	is_broken_ = true;
	Destroy();
}

bool ACover::HasCoveringOwner() const
{
	return has_covering_owner_;
}

void ACover::SetCoveringOwner(bool bHas_Covering_Owner)
{
	has_covering_owner_ = bHas_Covering_Owner;
}

bool ACover::IsBroken() const
{
	return is_broken_;
}

void ACover::SetIsBroken(bool bIs_Broken)
{
	is_broken_ = bIs_Broken;
}