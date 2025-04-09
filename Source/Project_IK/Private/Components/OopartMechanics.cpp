/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Source file for Oopart Mechanics class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/OopartMechanics.h"

#include "Characters/HeroBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Weapons/Ooparts/OopartBase.h"
#include "WorldSettings/IKGameInstance.h"


// Sets default values for this component's properties
UOopartMechanics::UOopartMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UOopartMechanics::BeginPlay()
{
	Super::BeginPlay();

	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

void UOopartMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (oopart_actor_)
	{
		oopart_actor_->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}

FOopartData UOopartMechanics::GetEquippedOopartData()
{
	return equipped_oopart_data_;
}

void UOopartMechanics::EquipOopart(EOopartType type)
{
	equipped_oopart_data_ = data_table_cache_->GetOopartData(type);
	if (oopart_actor_)
	{
		oopart_actor_->Destroy();
	}
	oopart_actor_ = GetWorld()->SpawnActor<AOopartBase>(equipped_oopart_data_.oopart_class, hero_cache_->oopart_pos_->GetComponentTransform());
	oopart_actor_->AttachToComponent(hero_cache_->oopart_pos_, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	oopart_actor_->SetOopartOwner(hero_cache_);
}

void UOopartMechanics::UnEquipOopart()
{
	equipped_oopart_data_ = data_table_cache_->GetOopartData(EOopartType::INVALID);
}
