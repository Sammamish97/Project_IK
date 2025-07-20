/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.18.2025
Summary : Header file for Buff Containing Cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Cover.h"
#include "Structs/BuffStatusData.h"
#include "Structs/BuffUIData.h"
#include "BuffContainingCover.generated.h"

UCLASS()
class PROJECT_IK_API ABuffContainingCover : public ACover
{
	GENERATED_BODY()

public:
	ABuffContainingCover();
	virtual void InitBuffData(const FItemData& item_data);
	virtual void BeginPlay() override;
	virtual void OnSettleDown(AActor* hidden_unit) override;
	virtual void OnLeave() override;
	
private:
	float buff_amount_;
	FBuffStatusData buff_status_;
	FBuffUIData buff_ui_data_;
};
