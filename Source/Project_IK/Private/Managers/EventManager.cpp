/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Manager

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/EventManager.h"

#include "Structs/EventData.h"

FEventData UEventManager::GetRandomEventData()
{
	if (event_table_)
	{
		return *event_table_->FindRow<FEventData>(FName("1"), TEXT(""));
	}
	return FEventData();
}

void UEventManager::GetResult(EEventResult result)
{
	switch (result)
	{
	case EEventResult::FirstEventResult_1:
		UE_LOG(LogTemp, Display, TEXT("EventManager::GetResult: First Event"));
		break;

	case EEventResult::FirstEventResult_2:
		UE_LOG(LogTemp, Display, TEXT("EventManager::GetResult: Second Event"));
		break;

	case EEventResult::FirstEventResult_3:
		UE_LOG(LogTemp, Display, TEXT("EventManager::GetResult: Third Event"));
			break;

	default:
		break;
	}
}