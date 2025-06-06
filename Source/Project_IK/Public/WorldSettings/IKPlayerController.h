/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Header file for Player Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Managers/EnumCluster.h"
#include "Structs/TargetParameters.h"
#include "IKPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UDelegateBridgeSubsystem;
class USupportSkillBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSKill, EHeroType, hero_idx);

UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend UDelegateBridgeSubsystem;

public:
	AIKPlayerController();
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();
	
	UFUNCTION()
	void ActivateSkillTargeting(EHeroType hero_type);

	UFUNCTION()
	void StartTargeting(const FTargetParameters& target_params, ETargetingState state, AActor* invoker = nullptr);

	UFUNCTION()
	void ClearTargetingState();
	
	void UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies);

protected:
	UPROPERTY()
	FOnActiveSKill on_active_skill_;

private:
	UFUNCTION()
	void ActivateFirstHeroActiveSkill();

	UFUNCTION()
	void ActivateSecondHeroActiveSkill();

	UFUNCTION()
	void ActivateThirdHeroActiveSkill();

	UFUNCTION()
	void ActivateFourthHeroActiveSkill();

	UFUNCTION()
	void ActivateFirstSupportSkill();
	
	UFUNCTION()
	void ActivateSecondSupportSkill();
	
	UFUNCTION()
	void ActivateThirdSupportSkill();
	
	UFUNCTION()
	void Decide();

	UFUNCTION()
	void CancelTargeting();

	UFUNCTION()
	void RotateCameraLeft();

	UFUNCTION()
	void RotateCameraRight();

	UFUNCTION()
	void OnToggleInventory();
	
protected:
	ETargetingState cur_targeting_state_ = ETargetingState::Idle;
	EHeroType selected_hero_type_ = EHeroType::INVALID;
	
	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	TObjectPtr<UTargetingComponent> targeting_component_;

	UPROPERTY(Transient)
	TObjectPtr<class AIKGameState> game_state_cache_;;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> player_input_mapping_context;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> decide_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> cancel_action_;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_first_hero_active_skill_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_second_hero_active_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_third_hero_active_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_fourth_hero_active_skill_action;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_first_support_skill_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_second_support_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_third_support_skill_action;
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_left_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_right_action_;
	//
	
	//IKTODO: 전투 레벨에서는 인벤토리를 열 수 없어야 한다! 그래서 이 IA는 Debug전용이다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> inventory_toggle_action_;
	//
};
