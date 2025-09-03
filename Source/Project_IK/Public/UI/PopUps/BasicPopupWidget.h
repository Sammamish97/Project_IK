/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Header file for Basic Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BasicPopupWidget.generated.h"

enum class EHeroType : uint8;
class UImage;
class UTextBlock;
class URichTextBlock;

//Basic Popup widget은 제일 기본적인 정보, 썸네일/이름/디테일을 나타내는 widget이다.
//이후 상황에 따라 이 클래스를 상속하여 액티브(쿨타임), 서포트(코스트), 무기(데미지/탄창/공격방식), 룬(세트효과)를 추가하여 구현한다.
UCLASS()
class PROJECT_IK_API UBasicPopupWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdatePopupData(UTexture2D* thumbnail, const FText& name, const FText& detail);
	void ResetWidget();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> thumbnail_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> name_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URichTextBlock> detail_;
};
