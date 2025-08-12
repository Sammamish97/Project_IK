/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Header file for perk node detail.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PerkNodeDetail.generated.h"

class UDisplayDataAsset;

USTRUCT()
struct PROJECT_IK_API FPerkNodeDetail
{
	GENERATED_BODY()

	//Name은 이름이자 이 detail의 Key로서 사용한다.
	//int32를 사용해도 되지만, 가독성을 위해 Text를 사용한다.
	UPROPERTY(EditAnywhere)
	FText name_;

	UPROPERTY(EditAnywhere)
	FText detail_;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> thumbnail = nullptr;
	
	UPROPERTY(EditAnywhere)
	int32 cost_;
	
	UPROPERTY(EditAnywhere)
	bool locked_;

	UPROPERTY(EditAnywhere)
	bool purchased_;
};
