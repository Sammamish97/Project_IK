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

	// Since OutVT.POV.AspectRatio is fixed number in init stages, manually calculated it in everyframes.
	float aspect_ratio = 1.7f;
	if (GEngine && GEngine->GameViewport)
	{
		FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();
		if (viewport_size.Y > 0)
		{
			aspect_ratio = (float)viewport_size.X / (float)viewport_size.Y;
		}
	}
	
	// Compute the distance needed to fit the bounding box within the camera frustum
	// OutVT.POV.FOV is vertical field of view
	const float half_height = FMath::Tan(FMath::DegreesToRadians(OutVT.POV.FOV * 0.5f));
	// Since extents is also half size of bounding box -> Half / Half
	const float required_vertical_distance = (extents.Y / half_height);
	const float required_horizontal_distance = extents.X / (half_height * aspect_ratio);
	// The extents.X & extents.Y are chosen by current fixed camera view vector (-1, 0.f, -100.f)
	FVector camera_location = center - (normalize_view_vector * FMath::Max(required_horizontal_distance, required_vertical_distance));

	TArray<FVector> box_corners;
	for (int32 i = 0; i < 8; ++i)
	{
		FVector corner = FVector(
			center.X + ((i & 1) ? extents.X : -extents.X),
			center.Y + ((i & 2) ? extents.Y : -extents.Y),
			center.Z + ((i & 4) ? extents.Z : -extents.Z)
		);
		box_corners.Add(corner);
	}

	APlayerController* pc = GetOwningPlayerController();
	TArray<FVector2D> screen_points;
	for (const FVector& corner : box_corners)
	{
		FVector2D screen_pos;
		// the third parameter preferred to be true when return a window or with letterbox,
		// default set by false for the full render target size.
		if (pc->ProjectWorldLocationToScreen(corner, screen_pos, true))
		{
			screen_points.Add(screen_pos);
		}
	}

	float left_most_x = FLT_MAX;
	for (const FVector2D& pos : screen_points)
	{
		left_most_x = FMath::Min(left_most_x, pos.X);
	}



	//// 1. How to get width in viewport.
	//// 2. Can I get a viewfrustum geometry?
	//// Adjust left alignment - Move the camera left so actors appear left-aligned.
	//FVector left_offset = normalize_view_vector.Rotation().Quaternion().GetRightVector() * extents.X;
	//camera_location += left_offset;

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