/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Source file for the minigun anim instance.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/#include "Animations/MinigunAnimInstance.h"

void UMinigunAnimInstance::SetMinigunState(EMinigunAnimState new_state)
{
	minigun_state_ = new_state;
}
