/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.02.2025
Summary : Header file for a random status buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Buffs/BuffHandler.h"
#include "BF_RandomBuff.generated.h"


struct FBuffStatusData;
enum class ECharacterStatType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UBF_RandomBuff : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;

protected:
	FBuffStatusData GetRandomBuff() const;
	inline ECharacterStatType GetRandomStatType() const;
	void GetRandomStatValue(FBuffStatusData buff_data) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	bool is_negative_value_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	bool is_permanent_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs")
	float duration_;
};
