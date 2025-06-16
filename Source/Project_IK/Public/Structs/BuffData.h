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
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	EBuffType buff_type_ = EBuffType::INVALID;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float duration_ = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_permanent_ = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	TArray<FBuffStatusData> buff_status_;
};
