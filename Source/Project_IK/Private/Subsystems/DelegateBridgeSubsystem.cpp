/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.27.2025
Summary : Source file for a subsystem that manages delegate bindings.
					Need to use this class to construct bindings for sake of LOOSE COUPLING

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/DelegateBridgeSubsystem.h"

AIKPlayerController* UDelegateBridgeSubsystem::GetAIKPlayerController() const
{
	APlayerController* raw_pc = GetWorld()->GetFirstPlayerController();

	if (raw_pc && raw_pc->IsA<AIKPlayerController>())
	{
		return Cast<AIKPlayerController>(raw_pc);
	}
	return nullptr;
}
