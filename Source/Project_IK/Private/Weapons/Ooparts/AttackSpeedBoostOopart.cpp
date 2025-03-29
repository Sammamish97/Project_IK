/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for attack speed boost oopart.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Ooparts/AttackSpeedBoostOopart.h"

#include "Characters/HeroBase.h"
#include "Structs/BuffData.h"


// Sets default values
AAttackSpeedBoostOopart::AAttackSpeedBoostOopart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	cool_down_ = 5.f;
	duration_ = 2.f;
	boost_amount_ = 100.f;
}

// Called when the game starts or when spawned
void AAttackSpeedBoostOopart::BeginPlay()
{
	Super::BeginPlay();
	FTimerDelegate boost_del = FTimerDelegate::CreateUObject(this, &AAttackSpeedBoostOopart::AttackSpeedBuff);
	GetWorld()->GetTimerManager().SetTimer(cool_time_handle_, boost_del ,cool_down_, true, cool_down_);
}

void AAttackSpeedBoostOopart::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(cool_time_handle_);
	Super::EndPlay(EndPlayReason);
}

void AAttackSpeedBoostOopart::AttackSpeedBuff()
{
	if(oopart_owner_ != nullptr)
	{
		auto casted_hero = Cast<AHeroBase>(oopart_owner_);
		casted_hero->ApplyBuff(FBuffData(TEXT("Oopart_AttackSpeedBoost"), ECharacterStatType::AttackSpeed, boost_amount_, false, duration_));
	}
}

// Called every frame
void AAttackSpeedBoostOopart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

