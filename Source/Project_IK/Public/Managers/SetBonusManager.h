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

UCLASS(Blueprintable)
class PROJECT_IK_API USetBonusManager : public UObject
{
	GENERATED_BODY()
public:
	TObjectPtr<USetBonusBase> GetSetBonus(ERuneSetType type);
	TArray<TPair<ERuneSetType, TArray<int32>>> FigureOutRuneSet(const TArray<TOptional<FRuneData>>& rune_slots);
private:
	TOptional<TPair<ERuneSetType, TArray<int32>>> FigureOutHexagonSet(const TArray<TOptional<FRuneData>>& rune_slot);
	TOptional<TPair<ERuneSetType, TArray<int32>>> FigureOutTriangleSet(const TArray<TOptional<FRuneData>>& rune_slots, TArray<int32>& indices, TArray<int32>& inv_indices);
	TArray<TPair<ERuneSetType, TArray<int32>>> FigureOutEdgeSet(const TArray<TOptional<FRuneData>>& rune_slot);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> chariot_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> great_bow_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> viper_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> dagger_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> poet_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> tempest_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bonus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusBase> quake_;
};
