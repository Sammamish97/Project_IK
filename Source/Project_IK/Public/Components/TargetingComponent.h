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
#include "Managers/EnumCluster.h"
#include "TargetingComponent.generated.h"

enum class ETargetingMode : uint8;
enum class ETargetType : uint8;

USTRUCT(BlueprintType)
struct FTargetParameters
{
	GENERATED_BODY()

	FTargetParameters(ETargetingMode mode = ETargetingMode::None, ETargetType type = ETargetType::All, float range = 0.f, float radius = 0.f)
		: current_mode_(mode), target_type_(type), range_(range), radius_(radius)
	{	}

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	ETargetingMode current_mode_;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	ETargetType target_type_;

	// How far selectable
	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	float range_;

	// A radius of selected area, an arc width for direction mode
	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	float radius_;
};

USTRUCT(BlueprintType)
struct FTargetResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	TArray<AActor*> target_actors_ = TArray<AActor*>();

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FVector target_location_ = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FRotator target_rotation_ = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FTargetParameters target_parameters_;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetResultSelected, const FTargetResult&, TargetResult);
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
	FOnTargetResultSelected OnTargetResultSelected;

	UPROPERTY(BlueprintAssignable, Category = "Targeting")
	FOnTargetingCanceled OnTargetingCanceled;

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void StartSkillTargeting(AActor* invoker, FTargetParameters TargetParams);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void StartItemTargeting(FTargetParameters TargetParams);
	UFUNCTION(BlueprintCallable, Category="Targeting")
	void StopTargeting();
	UFUNCTION()
	void StopTargetingIfInvokerIs(AActor* invoker);
	UFUNCTION()
	void StopItemTargeting();

	void CancelTargeting();
	void SetTargetingState(ETargetingState new_state);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* range_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* radius_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* arc_material_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	UMaterialInterface* highlight_material_;

private:
	ETargetingState targeting_state_ = ETargetingState::Idle;
	int32 selected_hero_idx_ = 0;
	
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
