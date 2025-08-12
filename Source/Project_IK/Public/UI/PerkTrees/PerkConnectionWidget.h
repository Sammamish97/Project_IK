/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Header file for perk connection widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/PerkConnectionColor.h"
#include "PerkConnectionWidget.generated.h"

class UPerkNodeWidget;

UCLASS()
class PROJECT_IK_API UPerkConnectionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitConnection(UPerkNodeWidget* owner, FVector2D end_point, FPerkConnectionColor connection_color);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	bool UpdateConnections(float duration);
	void SetLineConnectionTarget(bool purchase);
	FVector2D Vector2DLerp(float duration);
	
	
private:
	UPROPERTY(EditDefaultsOnly)
	FVector2D purchase_connection_target_;

	UPROPERTY(EditDefaultsOnly)
	FVector2D current_purchase_connection_;

	UPROPERTY(EditDefaultsOnly)
	FVector2D connection_end_point_;

	UPROPERTY()
	TObjectPtr<UPerkNodeWidget> owner_perk_node_;

	UPROPERTY(EditDefaultsOnly)
	FPerkConnectionColor connection_color_ = {FLinearColor::White, 1.0, {0.791667, 0.441022, 0}, 1.0};;

	float timer_;
};
