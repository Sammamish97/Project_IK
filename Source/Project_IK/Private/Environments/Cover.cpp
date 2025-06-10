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
#include "Subsystems/DelegateBridgeSubsystem.h"

// Sets default values
ACover::ACover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	cover_collider_ = CreateDefaultSubobject<UBoxComponent>(FName("cover_collider"));
	cover_position_ = CreateDefaultSubobject<USphereComponent>(FName("cover_position"));
	cover_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("cover_mesh"));

	cover_collider_->SetupAttachment(cover_position_);
	cover_collider_->SetMobility(EComponentMobility::Movable);
	
	cover_mesh_->SetupAttachment(cover_collider_);
	cover_mesh_->SetMobility(EComponentMobility::Movable);

	cover_position_->SetMobility(EComponentMobility::Static);

	SetRootComponent(cover_position_);
}

// Called when the game starts or when spawned
void ACover::BeginPlay()
{
	Super::BeginPlay();
}

void ACover::GetDamage(FDamageData data)
{
	hit_points_ -= data.atk_base_dmg_;
	hit_points_ -= data.skill_power_base_dmg_;

	if (hit_points_ < 0.f)
	{
		Die();
	}

	// Do not record damages worked on covers...
}

void ACover::SetHitPoints(float hit_points)
{
	hit_points_ = hit_points;
}

float ACover::GetHitPoints()
{
	return hit_points_;
}

void ACover::Die()
{
	if (AActor* hidden_actor = hidden_unit_.Get())
	{
		AUnit* casted_unit = Cast<AUnit>(hidden_actor);
		casted_unit->DispatchUnitEvent(EUnitEvent::LeaveCover);
	}
	is_broken_ = true;
	Destroy();
}

void ACover::SetMobility(EComponentMobility::Type type)
{
	cover_collider_->SetMobility(type);
	cover_position_->SetMobility(type);
	cover_mesh_->SetMobility(type);
}

bool ACover::HasCoveringOwner() const
{
	return hidden_unit_.IsValid();
}

void ACover::SetCoveringOwner(AActor* hided_actor)
{
	hidden_unit_ = hided_actor;
}

AActor* ACover::GetCoveringOwner()
{
	return hidden_unit_.Get();
}

bool ACover::IsBroken() const
{
	return is_broken_;
}

void ACover::SetIsBroken(bool bIs_Broken)
{
	is_broken_ = bIs_Broken;
}