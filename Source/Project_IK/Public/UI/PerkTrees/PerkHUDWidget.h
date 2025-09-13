/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.15.2025
Summary : Header file for perk HUD Widget

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PerkHUDWidget.generated.h"

class UButton;
class UTextBlock;
class UBorder;
class UPerkConnectionWidget;
struct FPerkNodeDetail;
class UPerkPopupWidget;
class UPerkProgressSubsystem;
class UTextManager;

UCLASS()
class PROJECT_IK_API UPerkHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	void SetPopupDetail(const FPerkNodeDetail& node_detail);
	void SetPerkPointText();
	bool IsMenuOpened() const;

	UFUNCTION()
	void ClosePerkTree();

private:
	//void UpdatePerkTreeConnectionOpacity();
	//void UpdatePerkTreeTransform();
	float ClampPerkConnectionOpacity(float value);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> parent_border_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> visibility_button_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> perk_tree_widget_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPerkPopupWidget> perk_popup_widget_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> perk_point_text_;

	UPROPERTY(Transient)
	TArray<UUserWidget*> perk_connections_cache_;
	
	UPROPERTY(Transient)
	TObjectPtr<UTextManager> text_manager_cache_;

	UPROPERTY(Transient)
	TObjectPtr<UPerkProgressSubsystem> progress_system_cache_;
	
	bool is_menu_opened_ = false;
	bool is_mouse_down_;
	FVector2D mouse_position_;
	float mouse_wheel_delta_;
};
