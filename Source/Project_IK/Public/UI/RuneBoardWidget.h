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
	virtual void NativeConstruct() override;
	void LoadRuneBoardWidget(int32 hero_idx);
	void UpdateRuneBoard(int32 hero_idx);
	void ClearSetBonusEffect();
	void UpdateSetBonusEffect();

private:
	TArray<FVector2D> ComputeVertices(float radius);
	TArray<Edge> ComputeEdges(const TArray<FVector2D>& vertices);
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UOverlay> rune_overlay_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UOverlay> line_overlay_ = nullptr;
	
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

	//
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_0_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_1_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_2_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_3_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_4_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_5_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_6_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_7_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_8_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_9_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_10_ = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<URuneBoardEdgeWidget> line_11_ = nullptr;
};
