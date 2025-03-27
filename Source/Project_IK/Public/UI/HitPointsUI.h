/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.13.2024
Summary : Header file for Skill Bar UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitPointsUI.generated.h"

enum class ECharacterStatType : uint8;
class UCharacterStatComponent;
class UCrowdControlComponent;
class UProgressBar;
class UHorizontalBox;
class UBuffDisplayer;
class UTextureManager;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UHitPointsUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindNecessaryComponents(UCharacterStatComponent* NewCharacterStat, UCrowdControlComponent* NewCrowdControl);


	UFUNCTION()
	void UpdateBuffWidgets();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	void UpdateHPWidget();

	UFUNCTION()
	void UpdateShieldWidget();

	UFUNCTION()
	void InitializeImages();

	UFUNCTION()
	void UpdateBuffDisplayers(TArray<TWeakObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const FLinearColor& background_color);

	UFUNCTION()
	void UpdateDebuffDisplayers(TArray<TWeakObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const TArray<ECCType>& appliedCCs, const FLinearColor& background_color);

	UFUNCTION()
	void UpdateDisplayer(UBuffDisplayer* displayer, UTexture2D* texture, const FLinearColor& color, int32 duplicated_count);

	UFUNCTION()
	void HideUnusedDisplayers(TArray<TWeakObjectPtr<UBuffDisplayer>>& displayers, int32 start_index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSubclassOf<UBuffDisplayer> buff_displayer_class_;

private:
	TWeakObjectPtr<UCharacterStatComponent> character_stat_;
	TWeakObjectPtr<UCrowdControlComponent> crowd_control_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UProgressBar> shield_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UProgressBar> hp_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UHorizontalBox> buffs_container_;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UHorizontalBox> debuffs_container_;

	UPROPERTY()
	TArray<TWeakObjectPtr<UBuffDisplayer>> debuff_displayers_;

	UPROPERTY()
	TArray<TWeakObjectPtr<UBuffDisplayer>> buff_displayers_;

	TWeakObjectPtr <const UTextureManager> texture_manager_;

	static constexpr int32 DISPLAYER_SIZE = 3;
};
