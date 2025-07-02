// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData.h"
#include "InventorySlot.generated.h"

class USlotDragDropImage;
class UInventoryWidget;

UCLASS()
class PROJECT_IK_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void SetImageTexture();

	void SetInventoryWidgetCache(UInventoryWidget* inventory_widget_cache);
	void ClearData();
	bool IsEmpty() const;
	
protected:
	UPROPERTY()
	EInventorySlotType slot_type_ = EInventorySlotType::INVALID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<USlotDragDropImage> dragdrop_image_class_;

	UPROPERTY(Transient)
	TObjectPtr<UInventoryWidget> inventory_widget_cache_;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> image_;
};
