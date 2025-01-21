/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Header file of checkbox button.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckboxButtonWidget.generated.h"

class UButton;
class UImage;
class FOnButtonClickedEvent;
struct FItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckboxButtonClickedDelegate);

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCheckboxButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	void SetItem(FItemData* item);
	FItemData* GetItem() const;
	void SetButtonTexture(UTexture2D* texture);

	void SetIsChecked(bool flag);
	void ToggleChecked();
	inline bool IsChecked() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCheckboxButtonClickedDelegate OnCheckboxButtonClickedDelegate;

	static constexpr FLinearColor normal_color = FLinearColor(0.69f, 0.69f, 0.69f);
	static constexpr FLinearColor hovered_color = FLinearColor(0.95f, 0.95f, 0.95f);
	static constexpr FLinearColor pressed_color = FLinearColor(0.5f, 0.5f, 0.5f);
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void UpdateImageColor();
	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UButton> button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TWeakObjectPtr<UImage> selection_indicator_image_;

	bool is_checked_;
	FItemData* item_data_;
};
