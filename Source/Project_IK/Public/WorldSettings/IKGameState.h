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
	const TArray<FSupportSkillData>& GetSupportSkillData() const;
	const TArray<TObjectPtr<USupportSkillBase>>& GetSupportSkillPtr() const;
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
	
private:
	UPROPERTY(VisibleAnywhere, Category = "EnergySystem")
	TObjectPtr<UEnergySystemComponent> energy_system_component_;
	
	UPROPERTY()
	TObjectPtr<AIKPlayerController> player_controller_cache_;
	
	UPROPERTY()
	TArray<TObjectPtr<USupportSkillBase>> equipped_support_skills_;

	UPROPERTY()
	TMap<EHeroType, FTimerHandle> active_skill_timers_;

	UPROPERTY()
	TMap<int32, FTimerHandle> support_skill_timers_;

	UPROPERTY()
	TObjectPtr<USkillBase> selected_skill_;

	EHeroType selected_hero_type_;
	int32 selected_support_num_;
	
	
	//
	//IKTODO:이 변수들은 테스트를 위한 변수들이다! 이후 BP에서 직접 설정해 주는 것이 아닌, UI 와 인벤토리를 통해 장착 되도록 변경되어야 한다.
	//UPROPERTY(Transient)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test Support Skills", meta = (AllowPrivateAccess = "true"))
	TArray<FSupportSkillData> support_skill_data_;
	
	//
};
