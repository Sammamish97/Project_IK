/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.12.2024
Summary : Source file for Smoke Region.
					It is an actor that will be presented on the game level when smoke region has been created.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SmokeRegion.h"

#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
ASmokeRegion::ASmokeRegion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = sphere_;
	sphere_->InitSphereRadius(0.f);
	sphere_->SetCollisionProfileName(TEXT("OverlapOnlyUnits"));
	sphere_->SetGenerateOverlapEvents(true);

	// Bind overlap events
	sphere_->OnComponentBeginOverlap.AddDynamic(this, &ASmokeRegion::OnSphereBeginOverlap);
	sphere_->OnComponentEndOverlap.AddDynamic(this, &ASmokeRegion::OnSphereEndOverlap);

	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

void ASmokeRegion::SetSphereRadius(float Radius)
{
	// It does not triggering physics or graphics update.
	sphere_->SetSphereRadius(Radius);

	float sphere_radius = sphere_->GetScaledSphereRadius();
	decal_->DecalSize = FVector(sphere_radius);
	decal_->MarkRenderStateDirty();
}

// Called when the game starts or when spawned
void ASmokeRegion::BeginPlay()
{
	Super::BeginPlay();

	if (visual_material_)
	{
		decal_->SetDecalMaterial(visual_material_);
	}
}

void ASmokeRegion::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AUnit* unit : overlapping_units_)
	{
		if (IsValid(unit))
		{
			RemoveEvasionBuff(unit);
		}
	}

	overlapping_units_.Empty();

	Super::EndPlay(EndPlayReason);
}

void ASmokeRegion::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnit* unit = Cast<AUnit>(OtherActor);
	if (unit && !overlapping_units_.Contains(unit))
	{
		overlapping_units_.Add(unit);
		ApplyEvasionBuff(unit);
	}
}

void ASmokeRegion::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnit* unit = Cast<AUnit>(OtherActor);
	if (unit && overlapping_units_.Contains(unit))
	{
		overlapping_units_.Remove(unit);
		RemoveEvasionBuff(unit);
	}
}

void ASmokeRegion::ApplyEvasionBuff(AUnit* unit)
{
	unit->ApplyBuff(FBuff(TEXT("SmokeRegion"), ECharacterStatType::EvasionRate, 0.5f, false, true));
}

void ASmokeRegion::RemoveEvasionBuff(AUnit* unit)
{
	unit->RemoveBuff(TEXT("SmokeRegion"));
}

