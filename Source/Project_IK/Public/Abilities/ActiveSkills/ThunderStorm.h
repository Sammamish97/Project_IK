/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Header file for an actor class for ThunderStorm.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThunderStorm.generated.h"

UCLASS()
class PROJECT_IK_API AThunderStorm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThunderStorm();

	UFUNCTION(BlueprintCallable)
	void SetSphereRadius(float Radius);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* visual_material_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UDecalComponent* decal_;

};
