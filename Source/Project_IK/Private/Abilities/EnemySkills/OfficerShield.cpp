/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.12.2024
Summary : Source file for Smoke Region.
					It is an actor that will be presented on the game level when smoke region has been created.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EnemySkills/OfficerShield.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Characters/Unit.h"

AOfficerShield::AOfficerShield()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = sphere_;
	sphere_->InitSphereRadius(0.f);
	sphere_->SetCollisionProfileName(TEXT("OverlapOnlyUnits"));
	sphere_->SetGenerateOverlapEvents(true);

	// Bind overlap events
	sphere_->OnComponentBeginOverlap.AddDynamic(this, &AOfficerShield::OnSphereBeginOverlap);
	sphere_->OnComponentEndOverlap.AddDynamic(this, &AOfficerShield::OnSphereEndOverlap);

	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

void AOfficerShield::SetSphereRadius(float Radius)
{
	// It does not triggering physics or graphics update.
	sphere_->SetSphereRadius(Radius);

	float sphere_radius = sphere_->GetScaledSphereRadius();
	decal_->DecalSize = FVector(sphere_radius);
	decal_->MarkRenderStateDirty();
}

void AOfficerShield::BeginPlay()
{
	Super::BeginPlay();
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
	SetSphereRadius(radius_);
	if (visual_material_)
	{
		decal_->SetDecalMaterial(visual_material_);
	}
}

void AOfficerShield::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AUnit* unit : overlapping_units_)
	{
		if (IsValid(unit))
		{
			buff_->RemoveBuff(unit);
		}
	}

	overlapping_units_.Empty();

	Super::EndPlay(EndPlayReason);
}

void AOfficerShield::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AUnit* unit = Cast<AUnit>(OtherActor))
	{
		if (unit->IsHero() == false && !overlapping_units_.Contains(unit))
		{
			overlapping_units_.Add(unit);
			buff_->ApplyBuff(unit);
		}
	}
	
}

void AOfficerShield::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AUnit* unit = Cast<AUnit>(OtherActor))
	{
		if (unit->IsHero() == false && overlapping_units_.Contains(unit))
		{
			overlapping_units_.Remove(unit);
			buff_->RemoveBuff(unit);
		}
	}
}