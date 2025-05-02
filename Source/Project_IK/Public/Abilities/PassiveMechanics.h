/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassiveMechanics.generated.h"

class APassiveSkill;
class AGun;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_IK_API UPassiveMechanics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveMechanics();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	void BeginPassive();
	void ActivatePassiveSkill();
	bool IsPassiveAvailable() const;
	
	void BanPassive(float duration);
	
	void OnStunned();
	float GetHoldTime() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PassiveMechanics", meta = (AllowPrivateAccess = "true", AllowedClass = "PassiveSkill"))
	UClass* passive_class_ = nullptr;

	UPROPERTY(Transient)
	APassiveSkill* passive_ref_ = nullptr;
	
	UPROPERTY(Transient)
	FTimerHandle hold_time_handle_;

	UPROPERTY(Transient)
	FTimerHandle ban_time_handle_;

	UPROPERTY(Transient)
	bool on_banned_;
};
