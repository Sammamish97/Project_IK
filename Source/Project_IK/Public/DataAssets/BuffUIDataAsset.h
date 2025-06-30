/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.19.2025
Summary : Header file for Buff Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/BuffUIData.h"
#include "BuffUIDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UBuffUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FBuffUIData GetBuffUIData(EBuffType type);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff Data", meta = (AllowPrivateAccess = "true"))
	TMap<EBuffType, FBuffUIData> buff_UI_data_;
};
