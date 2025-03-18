/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Header file for the Set Bonus Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnumCluster.h"
#include "Structs/RuneData.h"

#include "SetBonusManager.generated.h"

class USetBonusBase;

UCLASS()
class PROJECT_IK_API USetBonusManager : public UObject
{
	GENERATED_BODY()
public:
	TObjectPtr<USetBonusBase> GetSetBonus(ERuneSetType type);
	TArray<TPair<ERuneSetType, TArray<int32>>> FigureOutRuneSet(const TArray<FRuneData>& rune_data);
private:
	//SetBonusData
};
