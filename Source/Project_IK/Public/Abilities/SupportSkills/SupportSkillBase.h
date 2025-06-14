/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the Support Skill Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "UObject/Object.h"
#include "SupportSkillBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupportSkill, float , cool_time);

UCLASS(Abstract, Blueprintable)
class PROJECT_IK_API USupportSkillBase : public USkillBase
{
	GENERATED_BODY()
	
public:
	void InitSupportSkill();
	float GetCost() const;
	
	virtual bool ActivateSkill();
	virtual void Decide(const FTargetResult& TargetResult);
	virtual void Reset();
	virtual void OnDecide();

private:
	virtual void BeginCoolDown();
	virtual void UseEnergy();

protected:
	UPROPERTY()
	TObjectPtr<class AIKPlayerController> player_controller_cache_;
	TObjectPtr<class AIKGameState> game_state_cache_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float cost_ = 0.f;

	UPROPERTY()
	FTimerHandle cool_down_handle_;

public:
	UPROPERTY()
	FOnSupportSkill on_decide_;
};
