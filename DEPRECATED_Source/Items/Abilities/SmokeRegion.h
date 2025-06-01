/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.12.2024
Summary : Header file for Smoke Region.
					It is an actor that will be presented on the game level when smoke region has been created.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmokeRegion.generated.h"

class USphereComponent;
class UDecalComponent;
class AUnit;

UCLASS(Blueprintable)
class PROJECT_IK_API ASmokeRegion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmokeRegion();

	UFUNCTION(BlueprintCallable)
	void SetSphereRadius(float Radius);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UMaterialInterface* visual_material_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Smoke Region")
	USphereComponent* sphere_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Smoke Region")
	UDecalComponent* decal_;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyEvasionBuff(AUnit* unit);
	void RemoveEvasionBuff(AUnit* unit);

	TSet<AUnit*> overlapping_units_;
};
