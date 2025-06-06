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
class UCostUI;
class UTexture2D;
class UCreditWidget;
class USkillButtonWidget;

struct FTargetResult;


UCLASS()
class PROJECT_IK_API UButtonBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SynchroActiveSkillButtons(EHeroType hero_type);

	UFUNCTION()
	USkillButtonWidget* GetSkillButtonWidget(int32 idx);
	
	//IKTODO: 현재 액티브 스킬은 버튼 클릭 외에도 QWER입력을 통해 발동할 수 있다.
	//그러므로 침묵을 구현한다면, UI단이 아닌, SkillContainer단에서 구현해야 할 듯 하다.
	UFUNCTION()
	void SilenceSkill(AActor* character);
	void UnsilenceSkill(AActor* character);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void OnActiveSkillButtonClicked0();
	
	UFUNCTION()
	void OnActiveSkillButtonClicked1();
	
	UFUNCTION()
	void OnActiveSkillButtonClicked2();
	
	UFUNCTION()
	void OnActiveSkillButtonClicked3();

	//

	UFUNCTION()
	void OnSupportSkillButtonClicked0();
	
	UFUNCTION()
	void OnSupportSkillButtonClicked1();
	
	UFUNCTION()
	void OnSupportSkillButtonClicked2();

	//
	
	UFUNCTION()
	void FindCharacters();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
	UTexture2D* empty_item_icon;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> active_skill_button_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> active_skill_button_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> active_skill_button_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> active_skill_button_3_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillButtonWidget> support_skill_button_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillButtonWidget> support_skill_button_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USkillButtonWidget> support_skill_button_2_;

	//
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCostUI> cost_ui_;
	
	UPROPERTY(meta = (BindWidget))
	UCreditWidget* credit_widget_;

	UPROPERTY()
	TWeakObjectPtr<class AIKPlayerController> player_controller_cache_;

	UPROPERTY()
	TWeakObjectPtr<class AIKGameState> game_state_cache_;

	UPROPERTY()
	TArray<AActor*> characters_;

	TArray<TWeakObjectPtr<USkillContainer>> skill_containers_;
	
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> button_cooldown_materials_;

	bool is_item_muted_;
};
