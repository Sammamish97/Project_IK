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

class UTextBlock;
class UOverlay;
class USupportSkillPopupWidget;
class UActiveSkillPopupWidget;
class UBasicPopupWidget;
class URunePopupWidget;
class USupportSkillButtonWidget;
class USkillButtonWidget;
class UHeroWidget;
class UButton;
class UActiveSkillMechanics;
class UCostUI;
class UTexture2D;
class UCreditWidget;
class UImage;

struct FTargetResult;

UCLASS()
class PROJECT_IK_API UButtonBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	USupportSkillButtonWidget* GetSupportSkillButtonWidget(int32 idx);
	USkillButtonWidget* GetActiveSkillButtonWidget(EHeroType idx);
	UHeroWidget* GetHeroWidget(EHeroType idx);
	UActiveSkillPopupWidget* GetActiveSkillPopupWidget();
	USupportSkillPopupWidget* GetSupportSkillPopupWidget();
	UBasicPopupWidget* GetBuffPopupWidget();
	URunePopupWidget* GetRunePopupWidget();
	void ClearPopupWidget();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

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
	void OnStartTutorial();
	
	UFUNCTION()
	FEventReply OnExitTutorial(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
	UTexture2D* empty_item_icon;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroWidget> hero_widget_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroWidget> hero_widget_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroWidget> hero_widget_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroWidget> hero_widget_3_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillButtonWidget> support_skill_button_0_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillButtonWidget> support_skill_button_1_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillButtonWidget> support_skill_button_2_;

	//
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCostUI> cost_ui_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UActiveSkillPopupWidget> active_skill_popup_widget_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USupportSkillPopupWidget> support_skill_popup_widget_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicPopupWidget> buff_popup_widget_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URunePopupWidget> rune_popup_widget_;
	
	//
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> tutorial_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> background_image_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> active_skill_tutorial_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> support_skill_tutorial_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> speed_tutorial_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> camera_tutorial_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> exit_tutorial_;

	FTimerHandle tutorial_start_timer_;
	//
	
	UPROPERTY()
	TWeakObjectPtr<class AIKPlayerController> player_controller_cache_;

	UPROPERTY()
	TWeakObjectPtr<class AIKGameState> game_state_cache_;

	UPROPERTY()
	TArray<AActor*> characters_;

	TArray<TWeakObjectPtr<UActiveSkillMechanics>> skill_containers_;
	
	bool is_item_muted_;
};
