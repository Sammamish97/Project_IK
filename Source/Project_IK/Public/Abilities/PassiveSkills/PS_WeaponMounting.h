/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Header file for the weapon mounting passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "PassiveSkillBase.h"
#include "Structs/BuffStatusData.h"
#include "PS_WeaponMounting.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_IK_API UPS_WeaponMounting : public UPassiveSkillBase
{
	GENERATED_BODY()

public:
	virtual void InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data) override;

protected:
	UFUNCTION()
	void ApplyBuff();
	UFUNCTION()
	void RemoveBuff();

	bool is_buff_applied_ = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Passive Skills")
	FBuffStatusData buff_status_data_;
};
