/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Header file for GameState.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Structs/SupportSkillData.h"
#include "Structs/TargetResult.h"
#include "IKGameState.generated.h"

class USkillBase;
class UButtonBarWidget;
class AIKPlayerController;

UCLASS()
class PROJECT_IK_API AIKGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AIKGameState();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	bool UseEnergy(float amount);
	const TMap<int32, TObjectPtr<USupportSkillBase>>& GetSupportSkillPtr() const;
	UFUNCTION(BlueprintPure)
	class UEnergySystemComponent* GetEnergySystemComponent();
	UFUNCTION()
	void ActivateSkillTargeting(EHeroType hero_type);
	UFUNCTION()
	void ActivateSupportSkill(int32 support_num);
	UFUNCTION()
	bool OnDecide(const FTargetResult& result);
	UFUNCTION()
	void ClearTargetingState();
	UFUNCTION()
	void ReduceCoolDown(EHeroType hero_type, float amount);
	UFUNCTION()
	void ReduceCoolDownPercentage(EHeroType hero_type, float percentage);
	
private:
	UPROPERTY(VisibleAnywhere, Category = "EnergySystem")
	TObjectPtr<UEnergySystemComponent> energy_system_component_;
	
	UPROPERTY()
	TObjectPtr<AIKPlayerController> player_controller_cache_;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<USupportSkillBase>> equipped_support_skill_map_;

	UPROPERTY()
	TMap<EHeroType, FTimerHandle> active_skill_timers_;

	UPROPERTY()
	TMap<int32, FTimerHandle> support_skill_timers_;

	UPROPERTY()
	TObjectPtr<USkillBase> selected_skill_;

	UPROPERTY()
	TMap<int32, FItemData> equipped_support_skill_item_data_map_;
	
	EHeroType selected_hero_type_;
	int32 selected_support_num_;
};