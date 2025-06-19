// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffStatusData.h"
#include "UObject/Object.h"
#include "BuffData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FBuffData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	FText buff_name_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	EBuffType buff_type_ = EBuffType::INVALID;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY( BlueprintReadWrite, EditDefaultsOnly,Category = "Buff")
	float duration_ = 0.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	bool is_permanent_ = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	FString detail_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	TArray<FBuffStatusData> buff_status_;
};