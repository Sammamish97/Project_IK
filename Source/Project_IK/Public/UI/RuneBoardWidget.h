/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Header file for Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RuneBoardWidget.generated.h"

class URuneSlotWidget;

UCLASS()
class PROJECT_IK_API URuneBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	void InitBoardData(TObjectPtr<class URuneStorageWidget> storage_ptr);
	void LoadRuneBoardWidget(int32 hero_idx);
	void UpdateRuneBoard(int32 hero_idx);
	void ClearSelectedBorder();
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_0_ = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_1_ = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_2_ = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_3_ = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_4_ = nullptr;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneSlotWidget> slot_5_ = nullptr;
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<URuneSlotWidget>> slot_array_;
};
