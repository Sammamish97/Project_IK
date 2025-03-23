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

#include "Components/CapsuleComponent.h"

void AIKPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	const FVector normalize_view_vector = camera_view_vector_.GetSafeNormal();

	FBox bounding_box = GetHeroBox();

	FVector center = bounding_box.GetCenter();
	FVector extents = bounding_box.GetExtent();

	const FRotator camera_view_rotator = normalize_view_vector.Rotation();
	const FQuat camera_view_quaternion = camera_view_rotator.Quaternion();

	// Since OutVT.POV.AspectRatio is fixed number in init stages, manually calculated it in everyframes.
	float aspect_ratio = GetAspectRatio();

	// Compute the distance needed to fit the bounding box within the camera frustum
	const float tan = FMath::Tan(FMath::DegreesToRadians(GetFOVAngle() * 0.5f));
	// Since extents is also half size of bounding box -> Half / Half

	const FVector up_vector = camera_view_quaternion.GetUpVector();
	const FVector right_vector = camera_view_quaternion.GetRightVector();
	const FVector forward_vector = camera_view_quaternion.GetForwardVector();
	const float required_up_distance = FMath::Abs((FVector::DotProduct(up_vector, extents) * aspect_ratio) / tan);
	const float required_right_distance = FMath::Abs(FVector::DotProduct(right_vector, extents) / tan);
	const float required_forward_distance = FMath::Abs(FVector::DotProduct(forward_vector, extents));
	const float camera_distance = (FMath::Max(required_up_distance, FMath::Abs(required_right_distance)) + required_forward_distance) * zoom_padding_;
	FVector camera_location = center - (normalize_view_vector * camera_distance);


	DrawDebugDirectionalArrow(GetWorld(), center, center + forward_vector * required_forward_distance, 10.f, FColor::Cyan);
	DrawDebugDirectionalArrow(GetWorld(), center, center + right_vector * required_right_distance, 10.f, FColor::Magenta);
	DrawDebugDirectionalArrow(GetWorld(), center, center + up_vector * required_up_distance, 10.f, FColor::Yellow);
	
	
	float most_negative_Y = MAX_FLT;
	FVector corner_bounding_box_camera_space;
	for (int32 i = 0; i < 8; i++)
	{
		// Build the corner in local space
		FVector corner = FVector(
			(i & 1) ? -extents.X : extents.X,
			(i & 2) ? -extents.Y : extents.Y,
			(i & 4) ? -extents.Z : extents.Z
		);

		// Transform into camera space
		FVector camera_space_corner = camera_view_quaternion.UnrotateVector(corner);
		DrawDebugDirectionalArrow(GetWorld(), center, center + corner, 10.f, FColor::Emerald);

		if (camera_space_corner.Y < most_negative_Y)
		{
			most_negative_Y = camera_space_corner.Y;
			corner_bounding_box_camera_space = corner;
		}
	}
	corner_bounding_box_camera_space += center;

	APlayerController* pc = GetOwningPlayerController();

	// Adjust left alignment - Move the camera left so actors appear left-aligned.
	FVector pos = FVector::ZeroVector;
	FVector vec = FVector::ZeroVector;
	FVector left_edge_point = FVector::ZeroVector;
	FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();
	// Get left edge point.
	if (pc->DeprojectScreenPositionToWorld(0.f, viewport_size.Y / 2.f, pos, vec))
	{
		const float denominator = FVector::DotProduct(camera_view_vector_, vec);
		if (FMath::IsNearlyZero(denominator))
		{
			UE_LOG(LogTemp, Error, TEXT("Divided by zero in AIKPlayerCameraManager::UpdateViewTarget"));
		}
		// The old formula was it: (center.Z - camera_location.Z) / vec.Z;
		const float t = FVector::DotProduct(camera_view_vector_, (corner_bounding_box_camera_space - camera_location)) / denominator;
		left_edge_point = camera_location + vec * t;
	}
	DrawDebugDirectionalArrow(GetWorld(), corner_bounding_box_camera_space, left_edge_point, 10.f, FColor::Yellow);
	// It was an old formula to calculate left offset
	// (-normalize_view_vector.Rotation().Quaternion().GetRightVector())* (left_edged_point.Y - (center.Y - extents.Y) + left_edge_padding_);
	FVector left_offset = corner_bounding_box_camera_space - left_edge_point + (-normalize_view_vector.Rotation().Quaternion().GetRightVector()) * (left_edge_padding_);

	// camera_location += left_offset;


	OutVT.POV.Location = camera_location + camera_location_offset_;// FMath::VInterpTo(GetCameraLocation(), camera_location, DeltaTime, 2.f);
	OutVT.POV.Rotation = camera_view_rotator;

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

FBox AIKPlayerCameraManager::GetHeroBox() const
{
	FBox hero_box(EForceInit::ForceInit);
	for (TWeakObjectPtr<AActor> actor : tracked_heroes_)
	{
		if (actor.IsValid())
		{
			UCapsuleComponent* capsule = actor->FindComponentByClass<UCapsuleComponent>();
			if (capsule)
			{
				hero_box += capsule->Bounds.GetBox();
			}
			else
			{
				hero_box += actor->GetActorLocation();
			}
		}
	}
	return hero_box;
}

float AIKPlayerCameraManager::GetAspectRatio() const
{
	float aspect_ratio = 1.7f;
	if (GEngine && GEngine->GameViewport)
	{
		FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();
		if (viewport_size.Y > 0)
		{
			aspect_ratio = (float)viewport_size.X / (float)viewport_size.Y;
		}
	}

	return aspect_ratio;
}
