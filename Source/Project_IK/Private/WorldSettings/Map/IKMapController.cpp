/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map level player controller class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/Map/IKMapController.h"

#include "Kismet/GameplayStatics.h"

void AIKMapController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LevelChange", IE_Pressed, this, &AIKMapController::ChangeLevel);
}

void AIKMapController::ChangeLevel(FKey key)
{
	UE_LOG(LogTemp, Display, TEXT("Change Level"));
	UGameplayStatics::OpenLevel(GetWorld(), "DummyLevel");
}
