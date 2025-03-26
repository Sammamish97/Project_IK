/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.03.2024
Summary : Header file for Targeting component.
					Before skills invoked, it helps to choose target.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"

#include "TargetingComponent.generated.h"

enum class ETargetingMode : uint8;
enum class ETargetType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetingCanceled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable, Category = "Targeting")
	FOnTargetingCanceled OnTargetingCanceled;

	void CancelTargeting();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void StartTargeting(ETargetingState state, AActor* invoker, FTargetParameters target_params);

	UFUNCTION()
	void DecideAction();

	UFUNCTION()
	FTargetResult GetTargetResult();
	
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void StopTargeting();
	UFUNCTION()
	void StopTargetingIfInvokerIs(AActor* invoker);
	UFUNCTION()
	void StopItemTargeting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* range_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* radius_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* arc_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* highlight_material_;

private:
	void CleanUpVisuals();

private:
	UPROPERTY() 
	AActor* targeting_visual_actor_;
	bool is_targeting_;
	APlayerController* player_controller_;
	FTargetParameters target_parameters_;
	FTargetResult current_target_result_;

	// Components for visual feedback
	UPROPERTY()
	UDecalComponent* range_decal_;
	UPROPERTY()
	UDecalComponent* radius_decal_;
	UPROPERTY()
	UDecalComponent* sector_decal_;

	AActor* invoker_;

	UPROPERTY()
	UMaterialInstanceDynamic* highlight_dynamic_material_;

	TArray<UMaterialInterface*> original_materials_;
	AActor* previously_chosen_actor_;

	void HandleActorTargeting();
	void HandleLocationTargeting();
	void HandleDirectionTargeting();
	
	void InitializeTargetingVisuals();
	void UpdateTargetingVisuals();
	void CleanupTargetingVisuals();

	FVector ProjectPointOntoCircle(const FVector& Point, const FVector& Origin, float Radius);

	FVector GetGroundLocation() const;
	FVector ClampingOntoInvoker(const FVector& TargetLocation);
	
	// The function is for Actor targeting mode.
	AActor* FindClosestActor(const FVector& TargetLocation);
	void ApplyMaterialHighlight(AActor* target);

	bool IsWithinSector(const FVector& origin, const FVector& direction, float range, float angle, const FVector& actor_location);
	bool IsActorInRange(AActor* actor, float squared_range);

	void StartFocus();
	void EndFocus();
};
