/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Header file for the Set Bonus Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SetBonusBase.generated.h"

class AHeroBase;

UCLASS()
class PROJECT_IK_API USetBonusBase : public UObject
{
	GENERATED_BODY()

public:
	//전투 직전 실제로 효과를 적용하기위한 함수.
	void ActivateSetBonus(TObjectPtr<AHeroBase> owner, int32 set_amount);

protected:
	//2세트: 단순한 스테이터스 상승 효과.
	virtual void ActivateEdgeBonus();

	//3세트: 세트의 효과가 어느정도 나타나면서 다른 세트와 시너지를 낼 수 있는 효과.
	virtual void ActivateTriangleBonus();

	//6세트: 해당 세트의 이름의 이유를 나타내는 특징적인 효과.
	virtual void ActivateHexagonBonus();
	
protected:
	TObjectPtr<AHeroBase> hero_cache_;
};
