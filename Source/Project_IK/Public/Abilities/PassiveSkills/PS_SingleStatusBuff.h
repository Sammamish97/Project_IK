/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for the single status buff passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "PassiveSkillBase.h"
#include "PS_SingleStatusBuff.generated.h"

UCLASS()
class PROJECT_IK_API UPS_SingleStatusBuff : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> buff_;
};
