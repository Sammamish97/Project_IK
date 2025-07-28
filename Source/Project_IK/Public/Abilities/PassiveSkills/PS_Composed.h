/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Header file for the Composure passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "PassiveSkillBase.h"
#include "PS_Composed.generated.h"

class UBuffHandler;
UCLASS()
class PROJECT_IK_API UPS_Composed : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBuffHandler> buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> buff_;
	
	void OnHPChanged(float hp_ratio);

	UPROPERTY(EditDefaultsOnly)
	float min_hp_ratio_ = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float max_hp_ratio_ = 0.2f;

	bool is_buff_applied_ = false;
};
