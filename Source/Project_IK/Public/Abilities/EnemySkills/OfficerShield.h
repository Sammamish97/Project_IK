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
#include "OfficerShield.generated.h"
class UBuffHandler;
class USphereComponent;
class UDecalComponent;
class AUnit;

UCLASS()
class PROJECT_IK_API AOfficerShield : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AOfficerShield();

	UFUNCTION(BlueprintCallable)
	void SetSphereRadius(float Radius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> visual_material_;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float radius_;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> buff_class_;
	
	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> buff_;

	UPROPERTY(Transient)
	TObjectPtr<USphereComponent> sphere_;

	UPROPERTY(Transient)
	TObjectPtr<UDecalComponent> decal_;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(Transient)
	TSet<TObjectPtr<AUnit>> overlapping_units_;
};
