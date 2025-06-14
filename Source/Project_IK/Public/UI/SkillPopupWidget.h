/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Header file for Skill Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/SkillData.h"
#include "Components/TextBlock.h"
#include "SkillPopupWidget.generated.h"

enum class EHeroType : uint8;
class UImage;
class UTextBlock;

UCLASS()
class PROJECT_IK_API USkillPopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitHeroSkillData(const TMap<EHeroType, FSkillData>& input_data);
	void InitSupportSkillData(const TMap<int32, FSkillData>& input_data);

	void UpdateSkillPopupData(EHeroType type);
	void UpdateSkillPopupData(int32 support_skill_idx);
	
private:
	UPROPERTY()
	TMap<EHeroType, FSkillData> hero_skill_data_;

	UPROPERTY()
	TMap<int32, FSkillData> support_skill_data_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> skill_detail_;
};
