/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.11.2025
Summary : Header file for the buff that used globally.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "GlobalBuff.generated.h"

class UDisplayDataAsset;
class UGlobalBuffLogicBase;

USTRUCT(BlueprintType)
struct FGlobalBuffData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PassiveSkillData")
	TObjectPtr<UTexture2D> thumbnail_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGlobalBuffLogicBase> buff_logic_class_ = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 duration_ = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGlobalBuffType buff_type_ = EGlobalBuffType::None;
};