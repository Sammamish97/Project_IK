/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.23.2025
Summary : Header file for spanwer.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyBase;

UCLASS()
class PROJECT_IK_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateSpawner();

	void ActivateSpawner_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spawner")
	TSubclassOf<AEnemyBase> target_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spawner")
	int32 spawn_amount_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spawner")
	FRotator initial_rotation_;
};
