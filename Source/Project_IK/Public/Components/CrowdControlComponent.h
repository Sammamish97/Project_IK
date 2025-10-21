/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.23.2024
Summary : Header file to manage CC(crowd control) effects.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/EnumCluster.h"
#include "CrowdControlComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrowdControlChangedDelegate, TArray<ECCType>, applied_ccs);

class UDelegateBridgeSubsystem;

USTRUCT()
struct FBleedingData
{
	GENERATED_BODY()

	int32 tick_remains_;
	AActor* applier_;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UCrowdControlComponent : public UActorComponent
{
	GENERATED_BODY()

	friend UDelegateBridgeSubsystem;

private:
	constexpr static float BLEEDING_TICK_INTERVAL = 1.f;
	constexpr static float BLEEDING_DAMAGE = 5.f;
public:
	// Sets default values for this component's properties
	UCrowdControlComponent();

	UFUNCTION(BlueprintCallable)
	void ApplyCrowdControl(ECCType cc_type, float duration, AActor* applier = nullptr);

	UFUNCTION(BlueprintCallable)
	void RemoveCrowdControl(ECCType cc_type);

	UFUNCTION(BlueprintCallable)
	void RemoveAllCrowdControl();

	UFUNCTION(BlueprintCallable)
	bool HasCrowdControl(ECCType cc_type) const;

	UFUNCTION(BlueprintCallable)
	TArray<ECCType> GetAppliedCCArray() const;

protected:

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCrowdControlChangedDelegate OnCrowdControlChanged;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void BeginCC(ECCType cc_type, float duration, AActor* applier);
	void EndCC(ECCType cc_type);

	void Stun(float duration, bool is_applying = true);
	void Bleeding(float duration, AActor* applier, bool is_applying = true);
	void ApplyBleedDamage();

	TMap<ECCType, FTimerHandle> CC_timers_{};

	FTimerHandle bleeding_timer_{};

	TArray<FBleedingData> bleeding_remains_{};
};
