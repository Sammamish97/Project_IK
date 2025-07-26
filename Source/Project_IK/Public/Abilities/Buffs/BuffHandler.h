/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Header file for Buff Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Structs/FormattedText.h"
#include "UObject/Object.h"
#include "BuffHandler.generated.h"

class UDisplayDataAsset;
class AUnit;
enum class EBuffType : uint8;

UCLASS(Blueprintable)
class PROJECT_IK_API UBuffHandler : public UObject
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target);
	virtual void RemoveBuff(AUnit* target);
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	EBuffType buff_type_;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDisplayDataAsset> display_data_;

	UPROPERTY(Transient)
	TWeakObjectPtr<AUnit> target_cache_;
};