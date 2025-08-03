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
#include "Characters/Unit.h"

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

	const FVector up_vector = camera_view_quaternion.GetUpVector();
	const FVector right_vector = camera_view_quaternion.GetRightVector();
	const FVector forward_vector = camera_view_quaternion.GetForwardVector();

	FVector camera_location = ComputeCameraLocation(center, extents, normalize_view_vector, up_vector, right_vector, forward_vector, aspect_ratio);
	if (is_offset_applied_)
	{
		FVector camera_offset = ComputeCameraOffset(center, extents, camera_location, right_vector, up_vector, aspect_ratio) + camera_location_offset_;

		camera_location += camera_offset;
	}

	OutVT.POV.Location = FMath::VInterpTo(GetCameraLocation(), camera_location, DeltaTime, 2.f);
	OutVT.POV.Rotation = FMath::RInterpTo(GetCameraRotation(), camera_view_rotator, DeltaTime, 2.f);
}

void AIKPlayerCameraManager::AddEnemy(AActor* tracked_enemy)
{
	if (tracked_enemy)
	{
		tracked_enemies_.Add(tracked_enemy);
	}
}

void AIKPlayerCameraManager::RotateCameraLeft()
{
	RotateViewVector(rotation_step_in_degree_);
}

void AIKPlayerCameraManager::RotateCameraRight()
{
	RotateViewVector(-rotation_step_in_degree_);
}

void AIKPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	AIKGameModeBase* gamemode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
	for (const auto& elem : gamemode->GetHeroContainer())
	{
		if(elem != nullptr)
		{
			tracked_heroes_.Add(elem);
		}
	}
}

void AIKPlayerCameraManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	tracked_heroes_.Empty();
	tracked_enemies_.Empty();
}

FVector AIKPlayerCameraManager::ComputeCameraLocation(FVector center, FVector extents, FVector view_vector, FVector up_vector, FVector right_vector, FVector forward_vector, float aspect_ratio)
{
	const float tan = FMath::Tan(FMath::DegreesToRadians(GetFOVAngle() * 0.5f));


	// Since extents is also half size of bounding box -> Half / Half
	const float required_up_distance = FMath::Abs((FVector::DotProduct(up_vector, extents) * aspect_ratio) / tan);
	const float required_right_distance = FMath::Abs(FVector::DotProduct(right_vector, extents) / tan);
	const float required_forward_distance = FMath::Abs(FVector::DotProduct(forward_vector, extents));
	const float camera_distance = (FMath::Max(required_up_distance, FMath::Abs(required_right_distance)) + required_forward_distance) * zoom_padding_;
	
	return center - (view_vector * camera_distance);
}

FVector AIKPlayerCameraManager::ComputeCameraOffset(FVector center, FVector extents, FVector camera_location, FVector right_vector, FVector up_vector, float aspect_ratio)
{
	TArray<FVector> corner_candiates;
	for (int32 i = 0; i < 8; i++)
	{
		// Build the corner in local space
		FVector corner = center + FVector(
			(i & 1) ? -extents.X : extents.X,
			(i & 2) ? -extents.Y : extents.Y,
			(i & 4) ? -extents.Z : extents.Z
		);

		corner_candiates.Add(corner);
	}

	FVector hero_progress_vector;
	if (tracked_heroes_.IsValidIndex(0) && tracked_heroes_[0].IsValid())
	{
		hero_progress_vector = camera_view_vector_.Rotation().UnrotateVector(Cast<AUnit>(tracked_heroes_[0])->GetForwardDir());
	}
	else
	{
		hero_progress_vector = FVector(0.f, 1.f, 0.f);
	}


	FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();

	FVector vector = FVector::ZeroVector;
	float magnitude = 0.f;
	float padding = edge_padding_;

	if (FMath::Abs(hero_progress_vector.Y) > FMath::Abs(hero_progress_vector.Z))
	{
		if (hero_progress_vector.Y > 0)
		{
			// Adjust left alignment - Move the camera to right so actors appear left-aligned.
			FVector closest_box_corner_to_edge = GetClosestCorner(center, extents, FVector2D(-1.f, 0.f));
			FVector left_edge_point = ComputeEdgeWorldSpace(0.f, viewport_size.Y / 2.f, closest_box_corner_to_edge, camera_location);

			vector = right_vector;
			magnitude = FMath::Abs(FVector::DotProduct(closest_box_corner_to_edge - left_edge_point, right_vector));
		}
		else
		{
			// Adjust right alignment - Move the camera left so actors appear right-aligned.
			FVector closest_box_corner_to_edge = GetClosestCorner(center, extents, FVector2D(1.f, 0.f));
			FVector right_edge_point = ComputeEdgeWorldSpace(viewport_size.X, viewport_size.Y / 2.f, closest_box_corner_to_edge, camera_location);

			vector = -right_vector;
			magnitude = FMath::Abs(FVector::DotProduct(closest_box_corner_to_edge - right_edge_point, right_vector));
		}
	}
	else
	{
		// Adjust bottom alignment - Move the camera to down so actors appear bottom-aligned.
		FVector closest_box_corner_to_edge = GetClosestCorner(center, extents, FVector2D(0.f, 1.f));
		FVector bottom_edge_point = ComputeEdgeWorldSpace(viewport_size.X / 2.f, viewport_size.Y, closest_box_corner_to_edge, camera_location);
		
		vector = up_vector;
		magnitude = FMath::Abs(FVector::DotProduct(closest_box_corner_to_edge - bottom_edge_point, up_vector));

		// Multiplied by aspect-ratio
		padding /= aspect_ratio;		
	}

	if (magnitude > padding)
	{
		magnitude -= padding;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Padding is bigger than offset magnitude!"));
		magnitude = padding;
	}

	return (vector) * (magnitude);
}

FVector AIKPlayerCameraManager::ComputeEdgeWorldSpace(float screen_x, float screen_y, FVector closest_box_corner, FVector camera_location)
{
	APlayerController* pc = GetOwningPlayerController();
	FVector pos = FVector::ZeroVector;
	FVector vec = FVector::ZeroVector;
	FVector left_edge_point = FVector::ZeroVector;
	// Get left edge point.
	if (pc->DeprojectScreenPositionToWorld(screen_x, screen_y, pos, vec))
	{
		const float denominator = FVector::DotProduct(camera_view_vector_, vec);
		if (FMath::IsNearlyZero(denominator))
		{
			UE_LOG(LogTemp, Error, TEXT("Divided by zero in AIKPlayerCameraManager::UpdateViewTarget"));
		}
		const float t = FVector::DotProduct(camera_view_vector_, (closest_box_corner - camera_location)) / denominator;
		left_edge_point = camera_location + vec * t;
	}
	return left_edge_point;
}

FVector AIKPlayerCameraManager::GetClosestCorner(FVector center, FVector extents, FVector2D direction)
{
	TArray<FVector> corner_candiates;
	for (int32 i = 0; i < 8; i++)
	{
		// Build the corner in local space
		FVector corner = center + FVector(
			(i & 1) ? -extents.X : extents.X,
			(i & 2) ? -extents.Y : extents.Y,
			(i & 4) ? -extents.Z : extents.Z
		);

		corner_candiates.Add(corner);
	}

	APlayerController* pc = GetOwningPlayerController();
	FVector closest_box_corner_direction = FVector::ZeroVector;
	float biggest_magnitude = -FLT_MAX;
	for (const FVector& local_corner : corner_candiates)
	{
		FVector2D screen_position;
		pc->ProjectWorldLocationToScreen(local_corner, screen_position);
		float magnitude = FVector2D::DotProduct(screen_position, direction);
		if (magnitude > biggest_magnitude)
		{
			closest_box_corner_direction = local_corner;
			biggest_magnitude = magnitude;
		}
	}
	return closest_box_corner_direction;
}

void AIKPlayerCameraManager::RotateViewVector(float angle)
{
	FVector up_vector = FVector::UpVector;

	FQuat quatRotation = FQuat(up_vector, FMath::DegreesToRadians(angle));

	camera_view_vector_ = quatRotation.RotateVector(camera_view_vector_);
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
	for (TWeakObjectPtr<AActor> actor : tracked_enemies_)
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
