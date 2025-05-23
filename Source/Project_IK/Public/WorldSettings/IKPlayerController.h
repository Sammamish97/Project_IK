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
#include "IKPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UDelegateBridgeSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUsed, int32, item_idx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSKill, EHeroType, hero_idx);

UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend UDelegateBridgeSubsystem;

public:
	AIKPlayerController();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float dt) override;

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();
	
	UFUNCTION()
	void ActivateSkillTargeting(EHeroType hero_type);

	void UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies);
	
protected:
	virtual void BeginPlay();

	UPROPERTY()
	FOnItemUsed on_item_used_;

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
	void Decide();

	UFUNCTION()
	void CancelTargeting();

	UFUNCTION()
	void ToggleBetweenRepositionAndSupport();

	UFUNCTION()
	void EnterRepositioningMode();
	
	UFUNCTION()
	void RotateCameraLeft();

	UFUNCTION()
	void RotateCameraRight();

	UFUNCTION()
	void OnToggleInventory();
	
protected:
	ETargetingState targeting_state_ = ETargetingState::Idle;
	EHeroType selected_hero_type_ = EHeroType::INVALID;
	int32 selected_item_idx_ = -1;

	UPROPERTY(Transient)
	TObjectPtr<AActor> repositioning_hero_ = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	TObjectPtr<UTargetingComponent> targeting_component_;

	//
	float HARD_CODED_REPOSITION_RADIUS = 1000.f;
	const float max_cost_ = 10.f;
	float cur_cost_ = 0.f;

	UPROPERTY()
	TObjectPtr<class USupportSkillBase> equipped_support_skill_ = nullptr;
	//

public:
	float GetChargeTime() const;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> player_input_mapping_context;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> decide_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> cancel_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> support_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> enter_action_mode_action_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_first_hero_active_skill_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_second_hero_active_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_third_hero_active_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_fourth_hero_active_skill_action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_left_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_right_action_;

	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> inventory_toggle_action_;
};
