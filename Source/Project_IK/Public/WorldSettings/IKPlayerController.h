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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUsed, int32, item_idx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSKill, EHeroType, hero_idx);

UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AIKPlayerController();

	virtual void BeginPlay();
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();
	
	UPROPERTY()
	FOnItemUsed on_item_used_;
	
	UPROPERTY()
	FOnActiveSKill on_active_skill_;
	
	UFUNCTION()
	void ActivateSkillTargeting(EHeroType hero_type);

	UFUNCTION()
	void ActivateItemTargeting(int32 item_idx);

	void UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies);
	
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
	void ActivateFirstItem();

	UFUNCTION()
	void ActivateSecondItem();

	UFUNCTION()
	void ActivateThirdItem();
	
	UFUNCTION()
	void Decide();

	UFUNCTION()
	void CancelTargeting();

	UFUNCTION()
	void EnterRepositioningMode();

	UFUNCTION()
	void RotateCameraLeft();

	UFUNCTION()
	void RotateCameraRight();

protected:
	ETargetingState targeting_state_ = ETargetingState::Idle;
	EHeroType selected_hero_type_ = EHeroType::INVALID;
	int32 selected_item_idx_ = -1;
	
	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	TObjectPtr<UTargetingComponent> targeting_component_;

	//

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> player_input_mapping_context;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> decide_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> cancel_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> enter_repositioning_mode_action_;
	
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
	TObjectPtr<UInputAction> activate_first_item_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_second_item_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> activate_third_item_action_;

	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_left_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> rotate_camera_right_action_;
};
