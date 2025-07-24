/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.4.2025
Summary : Source file for Support skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "SupportSkillSlotWidget.generated.h"
class USupportSkillDataAsset;

UCLASS()
class PROJECT_IK_API USupportSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetSupportSkillSlotData(USupportSkillDataAsset* support_skill_data);
	USupportSkillDataAsset* GetStoredSupportSkillData();

private:
	UPROPERTY()
	TObjectPtr<USupportSkillDataAsset> support_skill_data_cache_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> image_;
};
