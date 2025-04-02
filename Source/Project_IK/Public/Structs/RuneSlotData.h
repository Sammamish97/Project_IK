// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneData.h"
#include "RuneSlotData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FRuneSlotData
{
public:
	GENERATED_BODY();
	FRuneSlotData(int32 idx = 0):rune_data(idx){};

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	FRuneData rune_data = FRuneData();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	bool is_empty = true;
};
