/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.10.2025
Summary : Source file for Outline Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/OutlineComponent.h"
void UOutlineComponent::BeginPlay()
{
	//IKTODO: 이 컴포넌트는 반드시 World에 BP_Outliner World Actor가 있어야 한다!
	//만약 없다면 여기서 생성을 하던, 터뜨리던 해야 한다.
	Super::BeginPlay();
}

void UOutlineComponent::SwitchOutline(UPrimitiveComponent* target, EOutlineState state)
{
	if(target)
	{
		if(state == EOutlineState::Disable)
		{
			target->SetRenderCustomDepth(false);
		}
		else
		{
			target->SetRenderCustomDepth(true);
			target->SetCustomDepthStencilValue(EnumToDepthStencilChannel(state));
		}
	}
}

int32 UOutlineComponent::EnumToDepthStencilChannel(EOutlineState state)
{
	switch(state)
	{
	case EOutlineState::Green:
		return 1;
	case EOutlineState::Red:
		return 2;
	case EOutlineState::Yellow:
		return 3;

		//IKTODO: 추후 예외처리 추가해야함.
	default:
		return 3;
	}
}
