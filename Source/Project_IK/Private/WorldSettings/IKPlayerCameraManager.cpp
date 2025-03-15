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

	FVector center_point = CalculateCenterPoint();

	FVector camera_location = center_point + camera_offsets_;
	FRotator view_rotator = (-camera_offsets_).Rotation();



	OutVT.POV.Location = FMath::VInterpTo(GetCameraLocation(), camera_location, DeltaTime, 2.f);
	OutVT.POV.Rotation = FMath::RInterpTo(GetCameraRotation(), view_rotator, DeltaTime, 2.f);
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

FVector AIKPlayerCameraManager::CalculateCenterPoint() const
{
	FVector sum = FVector::ZeroVector;

	for (TWeakObjectPtr<AActor> hero : tracked_heroes_)
	{
		if (hero.IsValid())
		{
			sum += hero->GetActorLocation();
		}
	}

	if (tracked_heroes_.Num() > 0)
	{
		return sum / tracked_heroes_.Num();
	}
	else
	{
		return FVector::ZeroVector;
	}
}