/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Manager

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "EnumCluster.h"
#include "Structs/EventData.h"
#include "UObject/Object.h"
#include "EventManager.generated.h"
UCLASS(Blueprintable)
class PROJECT_IK_API UEventManager : public UObject
{
	GENERATED_BODY()

public:
	FEventData GetRandomEventData();
	void GetResult(EEventResult result);
	
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Table", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UDataTable> event_table_;
};
