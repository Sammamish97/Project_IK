/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.12.2025
Summary : Header file for Ricochet active skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ActiveSkillBase.h"
#include "AT_Ricochet.generated.h"

class UBulletChainEffectComponent;
UCLASS(Abstract)
class PROJECT_IK_API UAT_Ricochet : public UActiveSkillBase
{
	GENERATED_BODY()
	
public:
	UAT_Ricochet();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
	void OnFinishSkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBulletChainEffectComponent> chain_on_hit_class_;
	
protected:
	float duration_ = 0.f;
	FTimerHandle duration_timer_handle_;
};
