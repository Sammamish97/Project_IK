/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.18.2025
Summary : Source file for Shock Javelin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/Skills/ShockJavelin.h"

#include "Characters/Unit.h"
#include "Components/BoxComponent.h"
#include "Environments/Cover.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"

// Sets default values
AShockJavelin::AShockJavelin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	collision_ = CreateDefaultSubobject<UBoxComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	javelin_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	javelin_mesh_->SetupAttachment(collision_);

	collision_->OnComponentBeginOverlap.AddDynamic(this, &AShockJavelin::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));

	movement_->InitialSpeed = 5000.f;
	movement_->ProjectileGravityScale = 0.f;

	dmg_data_.atk_base_dmg = 100.f;
	dmg_data_.damage_type = EDamageType::Explosive;
	
	SetRootComponent(collision_);
}

void AShockJavelin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);

	// Overlapped on Cover or Characters.
	if (casted_damage_logic)
	{
		dmg_data_.attack_target = OtherActor;
		if (OtherActor->IsA(ACover::StaticClass()))
		{
			dmg_data_.atk_base_dmg *= cover_dmg_scale_;
		}
		else
		{
			Cast<AUnit>(OtherActor)->GetStunned(stun_duration_);
		}
		if (casted_damage_logic) casted_damage_logic->GetDamage(dmg_data_);
	}

	// Overlapped on floor as far as I expected.
	else
	{
		BeginCooling();
	}
}

void AShockJavelin::SetDamageData(FDamageData dmg_data)
{
	dmg_data_ = dmg_data;
}

void AShockJavelin::BeginPlay()
{
	Super::BeginPlay();

	if (javelin_mesh_)
	{
		dynamic_material_instance_ = javelin_mesh_->CreateAndSetMaterialInstanceDynamic(0);
		dynamic_material_instance_->GetVectorParameterValue(FName("EmissiveColor"), init_emissive_);
	}
}

void AShockJavelin::BeginCooling()
{
	movement_->StopMovementImmediately();
	movement_->Velocity = FVector::ZeroVector;

	GetWorld()->GetTimerManager().SetTimer(cooling_timer_, this, &AShockJavelin::Cooling, cooling_step_, true);
}

void AShockJavelin::Cooling()
{
	cooling_alpha_ += cooling_step_;
	if (cooling_alpha_ >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(cooling_timer_);
	}

	UMaterialInstanceDynamic* instance = dynamic_material_instance_.Get();
	if (instance)
	{
		FLinearColor lerp_color = FMath::Lerp(init_emissive_, FLinearColor::Transparent, cooling_alpha_);
		instance->SetVectorParameterValue(FName("EmissiveColor"), lerp_color);
	}
}
