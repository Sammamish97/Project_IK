/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Structure for Active Skill data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "CharacterData.h"
#include "ItemData.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/EnumCluster.h"
#include "Managers/TextManager.h"
#include "WorldSettings/IKGameInstance.h"
#include "ActiveSkillData.generated.h"
class UIKGameInstance;
class UTextManager;

USTRUCT(BlueprintType)
struct PROJECT_IK_API FActiveSkillData
{
	GENERATED_BODY();
	UPROPERTY(EditDefaultsOnly)
	EActiveSkillType type_ = EActiveSkillType::INVALID;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UActiveSkillBase> active_skill_class;

	UPROPERTY(EditDefaultsOnly)
	FItemData item_data_;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<float> skill_power_scales_;

	UPROPERTY(EditDefaultsOnly)
	float cool_time_;
	
	//영웅에게 장착 되었을 시.
	FText BuildDetailText(UWorld* world, const FCharacterData& char_data)
	{
		UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world));
		UTextManager* text_manager = game_instance->GetTextManager();
		
		FText detail_base = text_manager->GetActiveSkillDetailText(item_data_.display_data_->text_key_);
		int32 scale_amount = skill_power_scales_.Num();
		
		//영웅에게 장착되어 있다면 총 데미지를 계산해야 한다.
		FFormatNamedArguments args;
		for (int32 i = 0; i < scale_amount; i++)
		{
			args.Add(FString::FromInt(i), FText::AsNumber(char_data.status_data_.skill_power_ * skill_power_scales_[i]));
		}
		FText detail = FText::Format(detail_base, args);
		return detail;
	}

	//영웅에게 장착 되지 않았을 시. (ex: Reward)
	FText BuildDetailText(UWorld* world)
	{
		UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(world));
		UTextManager* text_manager = game_instance->GetTextManager();
		
		FText detail_base = text_manager->GetActiveSkillDetailText(item_data_.display_data_->text_key_);
		int32 scale_amount = skill_power_scales_.Num();
		//1. 먼저 value에 해당하는 string을 format을 통해 조립한다.
		TArray<FText> val_elems;
		for (int32 i = 0; i < scale_amount; i++)
		{
			FText val_base = FText::FromString("({scale} x {stat})");
			
			FFormatNamedArguments val_args;
			val_args.Add("scale", FText::AsNumber(skill_power_scales_[i]));
			val_args.Add("stat", text_manager->GetStatusText(ECharacterStatType::SkillPower));

			val_base = FText::Format(val_base, val_args);
			val_elems.Add(val_base);
		}
		
		//2. base를 detail의 val에 넣는다.
		FFormatNamedArguments args;
		for (int32 i = 0; i < scale_amount; i++)
		{
			args.Add(FString::FromInt(i), val_elems[i]);
		}
		FText detail = FText::Format(detail_base, args);
		
		return detail;
	}
};
