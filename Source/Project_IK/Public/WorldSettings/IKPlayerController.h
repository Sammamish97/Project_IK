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

UCLASS()
class PROJECT_IK_API AIKPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AIKPlayerController();

	virtual void BeginPlay();
	virtual void SetupInputComponent() override;

	EPlayerState GetPlayerState() const;
	void SetPlayerState(EPlayerState new_state);

	UFUNCTION(BlueprintPure, Category = "Targeting")
	class UTargetingComponent* GetTargetingComponent();

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
	void EnterRepositioningMode();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Targeting")
	class UTargetingComponent* targeting_component_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> player_input_mapping_context;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> toggle_map_action_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> decide_action_;

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

	UPROPERTY(Transient)
	EPlayerState player_state_;
};
