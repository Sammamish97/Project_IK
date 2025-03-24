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

	// Since extents is also half size of bounding box -> Half / Half
	const float required_up_distance = FMath::Abs((FVector::DotProduct(up_vector, extents) * aspect_ratio) / tan);
	const float required_right_distance = FMath::Abs(FVector::DotProduct(right_vector, extents) / tan);
	const float required_forward_distance = FMath::Abs(FVector::DotProduct(forward_vector, extents));
	const float camera_distance = (FMath::Max(required_up_distance, FMath::Abs(required_right_distance)) + required_forward_distance) * zoom_padding_;
	FVector camera_location = center - (normalize_view_vector * camera_distance);

	camera_location += GetOffset(center, extents, camera_location) + camera_location_offset_;


	OutVT.POV.Location = FMath::VInterpTo(GetCameraLocation(), camera_location, DeltaTime, 2.f);
	OutVT.POV.Rotation = camera_view_rotator;

	DrawDebugBox(GetWorld(), bounding_box.GetCenter(), bounding_box.GetExtent(), FColor::Green, false, 0.f, 0.f, 2.f);
}

void AIKPlayerCameraManager::UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies)
{
	tracked_enemies_ = tracked_enemies;
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

FVector AIKPlayerCameraManager::GetOffset(FVector center, FVector extents, FVector camera_location)
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
	if (tracked_heroes_[0].IsValid())
	{
		hero_progress_vector = camera_view_vector_.Rotation().UnrotateVector(Cast<AUnit>(tracked_heroes_[0])->GetForwardDir());
	}
	else
	{

		hero_progress_vector = FVector(0.f, 1.f, 0.f);
	}

	if (FMath::Abs(hero_progress_vector.Y) > FMath::Abs(hero_progress_vector.Z))
	{
		FVector right_vector = camera_view_vector_.Rotation().Quaternion().GetRightVector();
		if (hero_progress_vector.Y > 0)
		{
			// Align left

			APlayerController* pc = GetOwningPlayerController();
			FVector corner_bounding_box_camera_space;
			float most_left_screen_point = FLT_MAX;
			for (const FVector& local_corner : corner_candiates)
			{
				FVector2D screen_position;
				pc->ProjectWorldLocationToScreen(local_corner, screen_position);
				if (screen_position.X < most_left_screen_point)
				{
					corner_bounding_box_camera_space = local_corner;
					most_left_screen_point = screen_position.X;
				}
			}

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
				const float t = FVector::DotProduct(camera_view_vector_, (corner_bounding_box_camera_space - camera_location)) / denominator;
				left_edge_point = camera_location + vec * t;
			}

			FVector tmp = (right_vector) * (FMath::Abs(FVector::DotProduct(corner_bounding_box_camera_space - left_edge_point, right_vector)) - edge_padding_);


			DrawDebugDirectionalArrow(GetWorld(), corner_bounding_box_camera_space, corner_bounding_box_camera_space + tmp, 5.f, FColor::Yellow);
			return tmp;
		}
		else
		{
			// Align right

			APlayerController* pc = GetOwningPlayerController();
			FVector corner_bounding_box_camera_space;
			float most_right_screen_point = -FLT_MAX;
			for (const FVector& local_corner : corner_candiates)
			{
				FVector2D screen_position;
				pc->ProjectWorldLocationToScreen(local_corner, screen_position);
				if (screen_position.X > most_right_screen_point)
				{
					corner_bounding_box_camera_space = local_corner;
					most_right_screen_point = screen_position.X;
				}
			}

			// Adjust right alignment - Move the camera left so actors appear right-aligned.
			FVector pos = FVector::ZeroVector;
			FVector vec = FVector::ZeroVector;
			FVector right_edge_point = FVector::ZeroVector;
			FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();
			// Get right edge point.
			if (pc->DeprojectScreenPositionToWorld(viewport_size.X, viewport_size.Y / 2.f, pos, vec))
			{
				const float denominator = FVector::DotProduct(camera_view_vector_, vec);
				if (FMath::IsNearlyZero(denominator))
				{
					UE_LOG(LogTemp, Error, TEXT("Divided by zero in AIKPlayerCameraManager::UpdateViewTarget"));
				}
				const float t = FVector::DotProduct(camera_view_vector_, (corner_bounding_box_camera_space - camera_location)) / denominator;
				right_edge_point = camera_location + vec * t;
			}

			FVector tmp = (-right_vector) * (FMath::Abs(FVector::DotProduct(corner_bounding_box_camera_space - right_edge_point, right_vector)) - edge_padding_);

			DrawDebugDirectionalArrow(GetWorld(), corner_bounding_box_camera_space, corner_bounding_box_camera_space + tmp, 5.f, FColor::Yellow);
			return tmp;
		}
	}
	else
	{
		// Align botton
		FVector up_vector = camera_view_vector_.Rotation().Quaternion().GetUpVector();

		APlayerController* pc = GetOwningPlayerController();
		FVector corner_bounding_box_camera_space;
		float most_bottom_screen_point = -FLT_MAX;
		for (const FVector& local_corner : corner_candiates)
		{
			FVector2D screen_position;
			pc->ProjectWorldLocationToScreen(local_corner, screen_position);
			if (screen_position.Y > most_bottom_screen_point)
			{
				corner_bounding_box_camera_space = local_corner;
				most_bottom_screen_point = screen_position.Y;
			}
		}

		// Adjust bottton alignment - Move the camera left so actors appear bottton-aligned.
		FVector pos = FVector::ZeroVector;
		FVector vec = FVector::ZeroVector;
		FVector botttom_edge_point = FVector::ZeroVector;
		FIntPoint viewport_size = GEngine->GameViewport->Viewport->GetSizeXY();
		// Get bottton edge point.
		if (pc->DeprojectScreenPositionToWorld(viewport_size.X / 2.f, viewport_size.Y, pos, vec))
		{
			const float denominator = FVector::DotProduct(camera_view_vector_, vec);
			if (FMath::IsNearlyZero(denominator))
			{
				UE_LOG(LogTemp, Error, TEXT("Divided by zero in AIKPlayerCameraManager::UpdateViewTarget"));
			}
			const float t = FVector::DotProduct(camera_view_vector_, (corner_bounding_box_camera_space - camera_location)) / denominator;
			botttom_edge_point = camera_location + vec * t;
		}

		FVector tmp = (up_vector) * (FMath::Abs(FVector::DotProduct(corner_bounding_box_camera_space - botttom_edge_point, up_vector)) - (edge_padding_ / GetAspectRatio()));
		DrawDebugDirectionalArrow(GetWorld(), corner_bounding_box_camera_space, botttom_edge_point, 5.f, FColor::Yellow);
		return tmp;
	}
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
