// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/TargetParameters.h"
#include "UObject/Object.h"
#include "SkillBase.generated.h"

struct FDamageData;
struct FBuffData;
struct FTargetResult;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecideSkill, float , cool_time);

UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void InitSkill();
	virtual bool ActivateSkill();
	virtual void Decide(const FTargetResult& TargetResult);
	virtual void OnDecide();
	virtual void Reset();
	virtual void BeginCoolDown();
	
	FTargetParameters GetTargetParameters() const;
	float GetCoolTime() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTargetParameters target_param_{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cool_time_ = 0.f;
	
	UPROPERTY()
	TObjectPtr<class AIKPlayerController> player_controller_cache_;

	UPROPERTY()
	FTimerHandle cool_down_handle_;
	
public:
	UPROPERTY()
	FOnDecideSkill on_decide_;
};
