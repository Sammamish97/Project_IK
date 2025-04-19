/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Source file for an actor class for ThunderStorm.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_ThunderStormActor.h"

#include "Components/DecalComponent.h"

// Sets default values
AAT_ThunderStormActor::AAT_ThunderStormActor()
{
	PrimaryActorTick.bCanEverTick = false;


	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

void AAT_ThunderStormActor::SetSphereRadius(float Radius)
{
	decal_->DecalSize = FVector(Radius);
	decal_->MarkRenderStateDirty();
}

// Called when the game starts or when spawned
void AAT_ThunderStormActor::BeginPlay()
{
	Super::BeginPlay();

	if (visual_material_)
	{
		decal_->SetDecalMaterial(visual_material_);
	}
}

