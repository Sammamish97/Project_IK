/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.24.2025
Summary : Header file for Quake Set Bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SetBonusBase.h"
#include "Structs/BuffStatusData.h"
#include "Structs/DamageData.h"
#include "SetBonus_Quake.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonus_Quake : public USetBonusBase
{
	GENERATED_BODY()
public:
	virtual void ActivateEdgeBonus() override;
	virtual void ActivateTriangleBonus() override;
	virtual void ActivateHexagonBonus() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> quake_ready_vfx_system_;

private:
	UFUNCTION()
	void TriangleAttackSpeedBuff();

	UFUNCTION()
	void HexagonSkillEcho();

	UFUNCTION()
	void HexagonSkillEchoReady();

private:
	float hexagon_effect_cooldown = 15.f;
	FTimerHandle skill_echo_timer_handle_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> edge_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> edge_buff_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBuffHandler> triangle_buff_class_;

	UPROPERTY();
	TObjectPtr<UBuffHandler> triangle_buff_;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> quake_ready_vfx_;
};
