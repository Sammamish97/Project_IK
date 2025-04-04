/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Level Widget class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/EventData.h"
#include "EventWidget.generated.h"

UCLASS()
class PROJECT_IK_API UEventWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitEventWidget(FEventData input_data);
	
	void OnPickFirstOption();
	void OnPickSecondOption();
	void OnPickThirdOption();

private:
	UPROPERTY(transient)
	TObjectPtr<class UEventManager> event_manager_cache_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UImage> situation_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UTextBlock> event_title_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UTextBlock> text_body_;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UButton> button_1_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UButton> button_2_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UButton> button_3_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UTextBlock> first_option_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UTextBlock> second_option_;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UTextBlock> third_option_;
};
