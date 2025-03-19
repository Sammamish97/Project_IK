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

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	FVector camera_view_vector_ = FVector(0.f, -500.f, -500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Movements")
	FVector camera_location_offset_ = FVector(0.f, 0.f, 0.f);
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FBox GetHeroBox() const;
	float GetAspectRatio() const;

	TArray<TWeakObjectPtr<AActor>> tracked_heroes_{};
};
