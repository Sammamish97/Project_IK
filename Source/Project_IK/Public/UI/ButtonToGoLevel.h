/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.26.2025
Summary : Header file of UI that contains a button to open a level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonToGoLevel.generated.h"

/**
 * 
 */

class UButton;

UCLASS(Blueprintable)
class PROJECT_IK_API UButtonToGoLevel : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTargetLevelName(FName target_level_name);
	FName GetTargetLevelName() const;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnOpenerButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> opener_button_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName target_level_name_;
};
