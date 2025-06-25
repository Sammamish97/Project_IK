/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.05.2025
Summary : Header file for Segmented HP UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "HPUICore.h"
#include "SegmentedHPUI.generated.h"

class UProgressBar;
UCLASS(Abstract, Blueprintable)
class PROJECT_IK_API USegmentedHPUI : public UHPUICore
{
	GENERATED_BODY()
public:
	virtual void UpdateWidget(float cur_hp, float cur_shield);
	
	UFUNCTION(BlueprintCallable)
	void SetMaterialSegmentWidth() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> separator_;
	
	UPROPERTY(Transient)
	float segment_amount = 50.f; 
};
