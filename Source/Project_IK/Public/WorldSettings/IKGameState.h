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
#include "Structs/TargetResult.h"
#include "IKGameState.generated.h"

class UTextManager;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleFocusMode, bool, on_detail_mode);

class USupportSkillBase;
class USupportSkillDataAsset;
class UActiveSkillMechanics;
class USkillBase;
class UButtonBarWidget;
class AIKPlayerController;

UCLASS()
class PROJECT_IK_API AIKGameState : public AGameStateBase
{
	GENERATED_BODY()

	enum class ESelectedSkill : uint8
	{
		INVALID,
		ActiveSkill,
		SupportSKill
	};
	
public:
	AIKGameState();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	bool UseEnergy(float amount);
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
	UFUNCTION()
	void ToggleFocusMode();

	const TArray<TObjectPtr<USupportSkillDataAsset>>& GetSupportSkillData();
	const TArray<TObjectPtr<USupportSkillBase>>& GetSupportSkills();

public:
	FOnToggleFocusMode OnToggleDetailMode;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USupportSkillDataAsset> relocation_data_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USupportSkillDataAsset> set_attack_target_data_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USupportSkillDataAsset> maintain_data_;
	
private:
	UPROPERTY()
	TObjectPtr<UEnergySystemComponent> energy_system_component_;
	
	UPROPERTY()
	TObjectPtr<AIKPlayerController> player_controller_cache_;

	UPROPERTY()
	TObjectPtr<UTextManager> text_manager_cache_;

	UPROPERTY()
	TMap<EHeroType, FTimerHandle> active_skill_timers_;

	UPROPERTY()
	TArray<TObjectPtr<USupportSkillDataAsset>> support_skill_data_;
	
	UPROPERTY()
	TArray<TObjectPtr<USupportSkillBase>> support_skills_;
	
	UPROPERTY()
	TArray<FTimerHandle> support_skill_timers_;

	UPROPERTY()
	TObjectPtr<UActiveSkillMechanics> selected_active_skill_mechanics_;

	UPROPERTY()
	TObjectPtr<USupportSkillBase> selected_support_skill_;
	
	ESelectedSkill selected_skill_type_;
	EHeroType selected_hero_type_;
	int32 selected_support_num_;

	bool on_focus_mode_ = false;
};