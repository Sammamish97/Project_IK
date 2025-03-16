/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.15.2025
Summary : Source file for player camaera manager that worked in Combat levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/IKPlayerCameraManager.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

void AIKPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	const FVector normalize_view_vector = camera_view_vector_.GetSafeNormal();

	FBox bounding_box(EForceInit::ForceInit);
	for (TWeakObjectPtr<AActor> actor : tracked_heroes_)
	{
		if (actor.IsValid())
		{
			bounding_box += actor->GetActorLocation();
		}
	}

	FVector center = bounding_box.GetCenter();
	FVector extents = bounding_box.GetExtent();
	
	// Compute the distance needed to fit the bounding box within the camera frustum
	// @@ TODO: extents.Size is radius of the box, while Tan(FOV/2) is height or width. It is not a valid logic.
	float required_distance = (extents.Size() / FMath::Tan(FMath::DegreesToRadians(OutVT.POV.FOV * 0.5f)));
	// New Camera Position - Move backwards along the view direction
	FVector camera_location = center - (normalize_view_vector * required_distance);

	// 1. How to get width in viewport.
	// 2. Can I get a viewfrustum geometry?
	// Adjust left alignment - Move the camera left so actors appear left-aligned.
	FVector left_offset = normalize_view_vector.Rotation().Quaternion().GetRightVector() * extents.X;
	camera_location += left_offset;

	OutVT.POV.Location = camera_location;// FMath::VInterpTo(GetCameraLocation(), camera_location, DeltaTime, 2.f);
	OutVT.POV.Rotation = normalize_view_vector.Rotation();

	DrawDebugBox(GetWorld(), bounding_box.GetCenter(), bounding_box.GetExtent(), FColor::Green, false, 0.f, 0.f, 2.f);
}

void AIKPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	AIKGameModeBase* gamemode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
	TArray<AActor*> heroes = gamemode->GetHeroContainers();
	for (TWeakObjectPtr<AActor> hero : heroes)
	{
		tracked_heroes_.Add(hero);
	}
}

void AIKPlayerCameraManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	tracked_heroes_.Empty();
}