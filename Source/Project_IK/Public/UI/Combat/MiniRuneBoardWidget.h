/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Heeader file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "MiniRuneBoardWidget.generated.h"

class URunePopupWidget;
class URuneBoardEdgeWidget;
class UMiniRuneSlotWidget;
class UImage;
class UOverlay;
UCLASS(Abstract)
class PROJECT_IK_API UMiniRuneBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	struct Edge
	{
		FVector2D mid_point;
		float length;
		float angle;
	};
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	void InitMiniRuneBoard(class URuneMechanics* rune_mechanics, URunePopupWidget* rune_popup_widget, EHeroType type);

private:
	TArray<FVector2D> ComputeVertices(float radius);
	TArray<Edge> ComputeEdges(const TArray<FVector2D>& vertices);
	
private:
	UPROPERTY()
	TObjectPtr<URunePopupWidget> rune_popup_widget_cache_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> border_;

	EHeroType hero_type_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> rune_overlay_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> line_overlay_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_3_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_4_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMiniRuneSlotWidget> rune_5_;

	//
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_0_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_1_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_2_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_3_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_4_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_5_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_6_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_7_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_8_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_9_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_10_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_11_ = nullptr;
};
