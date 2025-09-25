/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Header file for Map HUD Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapHUDWidget.generated.h"

class UGlobalBuffWidget;
class UTextBlock;
class UGlobalBuffPopupWidget;
class UBasicPopupWidget;
class UGlobalBuffDisplayer;
class UButton;
class UMapHeroWidget;
class UInventoryManager;
class UMapWidget;
class UUniformGridPanel;

UCLASS()
class PROJECT_IK_API UMapHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnOpenInventory();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMapWidget> map_widget_;

	//
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMapHeroWidget> hero_widget_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMapHeroWidget> hero_widget_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMapHeroWidget> hero_widget_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UMapHeroWidget> hero_widget_3_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> open_inventory_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> open_inventory_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGlobalBuffPopupWidget> global_buff_popup_widget_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> credit_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> credit_value_text_;

	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> global_buff_widget_holder_;

	UPROPERTY(transient)
	int32 grid_column_ = 4;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGlobalBuffWidget> global_buff_widget_class_;
	
	//
	UPROPERTY()
	TObjectPtr<UInventoryManager> inventory_manager_cache_;
};
