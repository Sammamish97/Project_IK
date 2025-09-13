/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.15.2025
Summary : Header file for player camaera manager that worked in Combat levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "IKPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API AIKPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	void AddEnemy(AActor* tracked_enemy);

	void RotateCameraLeft();
	void RotateCameraRight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	FVector camera_view_vector_ = FVector(0.f, -500.f, -500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	FVector camera_location_offset_ = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	float edge_padding_ = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	float zoom_padding_ = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovements")
	float rotation_step_in_degree_ = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovements")
	bool is_offset_applied_ = false;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	FVector ComputeCameraLocation(FVector center, FVector extents, FVector view_vector, FVector up_vector, FVector right_vector, FVector forward_vector, float aspect_ratio);
	FVector ComputeCameraOffset(FVector center, FVector extents, FVector camera_location, FVector right_vector, FVector up_vector, float aspect_ratio);
	FVector ComputeEdgeWorldSpace(float screen_x, float screen_y, FVector closest_box_corner, FVector camera_location);
	
	// Be careful of screen space, top-left corner is (0, 0)
	FVector GetClosestCorner(FVector center, FVector extents, FVector2D direction);

	void RotateViewVector(float angle);

	FBox GetHeroBox() const;
	float GetAspectRatio() const;

	void LoadHeroes();

	TArray<TWeakObjectPtr<AActor>> tracked_heroes_{};
	TArray<TWeakObjectPtr<AActor>> tracked_enemies_{};
};
