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
#include "Managers/EnumCluster.h"
#include "RuneBoardWidget.generated.h"
class UInventoryWidget;
class URuneSlotWidget;
class URuneBoardEdgeWidget;
class UOverlay;
UCLASS()
class PROJECT_IK_API URuneBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	struct Edge
	{
		FVector2D mid_point;
		float length;
		float angle;
	};
public:
	void SetInventoryWidget(UInventoryWidget* widget_ptr);
	virtual void NativeConstruct() override;
	//Spawn data를 탐색하며 살아있는 최초의 영웅의 rune board를 load.
	void LoadRuneBoardWidget();
	//선택된 하나의 rune board를 load.
	void LoadRuneBoardWidget(EHeroType hero_type);
	void UpdateRuneBoard();
	void ClearSetBonusEffect();
	void UpdateSetBonusEffect();
	TObjectPtr<URuneSlotWidget> GetRuneSlotWidget(int32 idx);
	void ToggleReadOnly(bool is_read_only);

private:
	TArray<FVector2D> ComputeVertices(float radius);
	TArray<Edge> ComputeEdges(const TArray<FVector2D>& vertices);
	
private:
	EHeroType cur_hero_type_ = EHeroType::INVALID;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> rune_overlay_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> line_overlay_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_0_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_1_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_2_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_3_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_4_ = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneSlotWidget> slot_5_ = nullptr;

	//
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_0_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_1_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_2_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_3_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_4_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_5_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_6_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_7_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_8_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_9_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_10_ = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_11_ = nullptr;
};
