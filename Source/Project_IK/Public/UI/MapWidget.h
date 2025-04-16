/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.05.2024
Summary : Header file for displaying maps.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UScrollBox;
class UGridPanel;
class UGridSlot;
class UButton;
class UImage;

class UIKMaps;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMapWidget(const FObjectInitializer& object_initializer);
	virtual bool Initialize() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI images")
	UTexture2D* enemy_icon_texture_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI images")
	UTexture2D* boss_icon_texture_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI images")
	UTexture2D* store_icon_texture_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI images")
	UTexture2D* event_icon_texture_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI images")
	UTexture2D* check_texture_;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void InitializeWidgetTree();
	void InitializeButtons();
	void InitializeWidgets();

	FVector2D GetButtonPosition(TWeakObjectPtr<UButton> button) const;
	void EnableReachableButtons();
	void EnableZeroLevelButtons();

	void SetSlotRowCol(UGridSlot* GridSlot, int32 Row, int32 Column);

	UFUNCTION()
	void OpenLevel();

	UPROPERTY()
	TObjectPtr<UCanvasPanel> root_canvas_panel_;

	UPROPERTY()
	TObjectPtr<UBorder> background_border_;

	UPROPERTY()
	TObjectPtr<UScrollBox> scroll_box_;

	UPROPERTY()
	TObjectPtr<UGridPanel> buttons_holder_;

	UPROPERTY()
	TMap<FIntPoint, TObjectPtr<UButton>> buttons_;

	UPROPERTY()
	TArray<TObjectPtr<UImage>> check_images_;

	UPROPERTY()
	TWeakObjectPtr<const UIKMaps> maps_;
};
