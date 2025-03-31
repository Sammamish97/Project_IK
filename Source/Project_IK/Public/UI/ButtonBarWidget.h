/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Header file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "ButtonBarWidget.generated.h"

class UButton;
class USkillContainer;
class UItemInventory;
struct FTargetResult;
class UTexture2D;
class UCreditWidget;

UCLASS()
class PROJECT_IK_API UButtonBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SynchroItemButtons(int32 item_idx);

	UFUNCTION()
	void SynchroActiveSkillButtons(EHeroType hero_type);

	UFUNCTION()
	void SilenceSkill(AActor* character);
	void UnsilenceSkill(AActor* character);

	UFUNCTION()
	void MuteItems();
	UFUNCTION()
	void UnmuteItems();
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void OnSkillButtonClicked0();
	
	UFUNCTION()
	void OnSkillButtonClicked1();
	
	UFUNCTION()
	void OnSkillButtonClicked2();
	
	UFUNCTION()
	void OnSkillButtonClicked3();

	UFUNCTION()
	void ActivateSkillTargeting(EHeroType caster);

	UFUNCTION()
	void OnItemButtonClicked0();
	
	UFUNCTION()
	void OnItemButtonClicked1();
	
	UFUNCTION()
	void OnItemButtonClicked2();

	UFUNCTION()
	void ActivateItemTargeting(int32 item_idx);
	
	UFUNCTION()
	void FindCharacters();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill_button_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill_button_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill_button_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> skill_button_3_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> item_button_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> item_button_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> item_button_2_;
	
	UPROPERTY(meta = (BindWidget))
	UCreditWidget* credit_widget_;

	UPROPERTY()
	TWeakObjectPtr<class AIKPlayerController> player_controller_cache_;

	UPROPERTY()
	TArray<AActor*> characters_;

	TArray<TWeakObjectPtr<USkillContainer>> skill_containers_;
	
	TWeakObjectPtr<UItemInventory> item_inventory_;

	UPROPERTY()
	UTexture2D* empty_item_icon;

	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> button_cooldown_materials_;
	TArray<float> cooldowns_;

	bool is_item_muted_;
};
