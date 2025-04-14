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
enum class ECCType : uint8;
class UProgressBar;
class UHorizontalBox;
class UBuffDisplayer;
class UTextureManager;
class UDataTableManager;
struct FBuffData;


/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UHitPointsUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateAppliedBuffs(TArray<FBuffData> applied_buffs);

	UFUNCTION()
	void UpdateAppliedCCs(TArray<ECCType> applied_ccs);

	UFUNCTION()
	void UpdateHPWidget(float hp_ratio);

	UFUNCTION()
	void UpdateShieldWidget(float shield_ratio);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	void InitializeImages();


	void UpdateBuffWidgets();

	void UpdateBuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const FLinearColor& background_color);

	void UpdateDebuffDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, const TMap<ECharacterStatType, int32>& counts, const TArray<ECCType>& appliedCCs, const FLinearColor& background_color);

	void UpdateDisplayer(UBuffDisplayer* displayer, UTexture2D* texture, const FLinearColor& color, int32 duplicated_count);

	void HideUnusedDisplayers(TArray<TObjectPtr<UBuffDisplayer>>& displayers, int32 start_index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
	TSubclassOf<UBuffDisplayer> buff_displayer_class_;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> shield_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> hp_progress_bar_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> buffs_container_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> debuffs_container_;

	UPROPERTY()
	TArray<TObjectPtr<UBuffDisplayer>> debuff_displayers_;

	UPROPERTY()
	TArray<TObjectPtr<UBuffDisplayer>> buff_displayers_;

	TWeakObjectPtr <UDataTableManager> data_table_manager_;

	static constexpr int32 DISPLAYER_SIZE = 3;

	TArray<FBuffData> buffs_array_;
	TArray<ECCType> ccs_array_;
};
