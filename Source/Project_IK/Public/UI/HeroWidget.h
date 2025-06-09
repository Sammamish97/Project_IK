/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.06.2025
Summary : Header file for Hero widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeroWidget.generated.h"

enum class ECharacterStatType : uint8;
enum class ECCType : uint8;
class UHP_UI_Widget;
class UHorizontalBox;
class UBuffDisplayer;
class UDataTableManager;
struct FBuffData;

UCLASS()
class PROJECT_IK_API UHeroWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InitHeroWidget(class URuneMechanics* rune_mechanics, float max_hp, float cur_hp);
	UHP_UI_Widget* GetHPWidget();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMiniRuneBoardWidget> mini_rune_board_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHP_UI_Widget> hp_bar_;
	
public:
	UFUNCTION()
	void UpdateAppliedBuffs(TArray<FBuffData> applied_buffs);

	UFUNCTION()
	void UpdateAppliedCCs(TArray<ECCType> applied_ccs);

protected:
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
