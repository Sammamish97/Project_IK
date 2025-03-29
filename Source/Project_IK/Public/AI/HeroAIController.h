/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.29.2025
Summary : Header file for Hero AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GunnerAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "HeroAIController.generated.h"

UCLASS()
class PROJECT_IK_API AHeroAIController : public AGunnerAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHeroAIController();
	void RepositionHero(FVector target_location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void OnArrivedTargetPosition(FAIRequestID request_id, const FPathFollowingResult& result);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HeroAIController", meta = (AllowPrivateAccess = "true"))
	FName target_position_key_name_;
};
