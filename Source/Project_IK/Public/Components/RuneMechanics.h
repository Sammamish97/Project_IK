/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.8.2025
Summary : Header file for the Rune Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Managers/EnumCluster.h"
#include "Structs/RuneData.h"
#include "RuneMechanics.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_IK_API URuneMechanics : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	URuneMechanics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<TPair<ERuneSetType, TArray<int32>>> FigureOutRuneSet();
	
public:
	FString RuneEnumToString(ERuneSetType set_type);
	void SetRune(FRuneData rune);
	FStatusData GetTotalStatus();
	void ApplySetBonuses();
	
private:
	UPROPERTY()
	TArray<FRuneData> rune_slots_;
	
	UPROPERTY(Transient)
	TObjectPtr<class USetBonusManager> bonus_manager_cache_;

	UPROPERTY(Transient)
	TObjectPtr<class AHeroBase> hero_cache_;
};
