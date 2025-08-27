/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.27.2024
Summary : Header file for UI that displays global buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GlobalBuffDisplayer.generated.h"

class UUniformGridPanel;

UCLASS()
class PROJECT_IK_API UGlobalBuffDisplayer : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> global_buff_widget_holder_;

	UPROPERTY(transient)
	int32 grid_column_ = 4;
};
