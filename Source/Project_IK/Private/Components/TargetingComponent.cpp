/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.03.2024
Summary : Source file for Targeting component.
					Before skills invoked, it helps to choose target.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/TargetingComponent.h"
#include "Managers/EnumCluster.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "WorldSettings/IKPlayerController.h"
#include "Engine/World.h"
#include "WorldSettings/IKGameModeBase.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	is_targeting_ = false;
}

// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	player_controller_ = Cast<AIKPlayerController>(GetOwner());

	InitializeTargetingVisuals();
}

void UTargetingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (targeting_visual_actor_)
	{
		targeting_visual_actor_->Destroy();
		targeting_visual_actor_ = nullptr;
	}
	OnTargetingCanceled.Clear();
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!is_targeting_ || !player_controller_)
	{
		return;
	}
	UpdateTargetingVisuals();
}

void UTargetingComponent::CancelTargeting()
{
	OnTargetingCanceled.Broadcast();
	StopTargeting();
}

void UTargetingComponent::CleanUpVisuals()
{
	UMaterialInstanceDynamic* dynamic_material = nullptr;
	switch (target_parameters_.current_mode_)
	{
	case ETargetingMode::None:
		break;
	case ETargetingMode::Actor:
		player_controller_->CurrentMouseCursor = EMouseCursor::Crosshairs;
		radius_decal_->SetVisibility(false);
		range_decal_->SetVisibility(true);
		sector_decal_->SetVisibility(false);
		break;
	case ETargetingMode::Location:
		player_controller_->CurrentMouseCursor = EMouseCursor::GrabHand;
		radius_decal_->DecalSize = FVector(target_parameters_.radius_);
		radius_decal_->SetVisibility(true);
		range_decal_->SetVisibility(true);
		sector_decal_->SetVisibility(false);
		break;
	case ETargetingMode::Direction:
		radius_decal_->SetVisibility(false);
		range_decal_->SetVisibility(true);
		sector_decal_->SetVisibility(true);
		sector_decal_->DecalSize = FVector(target_parameters_.range_);
		dynamic_material = sector_decal_->CreateDynamicMaterialInstance();
		if (dynamic_material)
		{
			dynamic_material->SetScalarParameterValue(FName("ArcWidth"), target_parameters_.radius_ / 360);
		}
		break;
	default:
		break;
	}
}

void UTargetingComponent::StartTargeting(FTargetParameters target_params, AActor* invoker)
{
	StartFocus();

	is_targeting_ = true;
	invoker_ = invoker;
	target_parameters_ = target_params;
	current_target_result_.target_actors_.Empty();
	current_target_result_.target_parameters_ = target_parameters_;
	range_decal_->DecalSize = FVector(target_parameters_.range_);

	CleanUpVisuals();
}

FTargetResult UTargetingComponent::DecideTargetings()
{
	switch (target_parameters_.current_mode_)
	{
	case ETargetingMode::None:
		StopTargeting();
		break;
	case ETargetingMode::Actor:
		HandleActorTargeting();
		break;
	case ETargetingMode::Location:
		HandleLocationTargeting();
		break;
	case ETargetingMode::Direction:
		HandleDirectionTargeting();
		break;
	default:
		break;
	}
	return current_target_result_;
}

void UTargetingComponent::StopTargeting()
{
	EndFocus();
	is_targeting_ = false;
	target_parameters_ = FTargetParameters();
	player_controller_->CurrentMouseCursor = EMouseCursor::Default;
	CleanupTargetingVisuals();
}

void UTargetingComponent::StopTargetingIfInvokerIs(AActor* invoker)
{
	if (is_targeting_)
	{
		if (invoker_ == invoker)
		{
			StopTargeting();
		}
	}
}

void UTargetingComponent::StopItemTargeting()
{
	if (is_targeting_)
	{
		if (invoker_ == nullptr)
		{
			StopTargeting();
		}
	}
}

void UTargetingComponent::HandleActorTargeting()
{
	FVector target_location = GetGroundLocation();
	AActor* closest_actor = FindClosestActor(target_location);

	current_target_result_.target_location_ = target_location;
	current_target_result_.target_actors_.Add(closest_actor);

	StopTargeting();
}

void UTargetingComponent::HandleLocationTargeting()
{
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FVector target_location = GetGroundLocation();
	current_target_result_.target_location_ = ClampingOntoInvoker(target_location);

	if (game_mode_cache)
	{
		const float squared_radius = target_parameters_.radius_ * target_parameters_.radius_;
		if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Allies)
		{
			auto heroes = game_mode_cache->GetHeroContainer();

			for (AActor* actor : heroes)
			{
				FVector to_actor = actor->GetActorLocation() - current_target_result_.target_location_;

				float squared_distance_to_actor = to_actor.SizeSquared();
				if (squared_distance_to_actor <= squared_radius)
				{
					current_target_result_.target_actors_.Add(actor);
				}
			}
		}
		if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Opponents)
		{
			auto enemies = game_mode_cache->GetEnemyContainers();

			for (AActor* actor : enemies)
			{
				FVector to_actor = actor->GetActorLocation() - current_target_result_.target_location_;

				float squared_distance_to_actor = to_actor.SizeSquared();
				if (squared_distance_to_actor <= squared_radius)
				{
					current_target_result_.target_actors_.Add(actor);
				}
			}
		}
	}

	StopTargeting();
}

void UTargetingComponent::HandleDirectionTargeting()
{
	if (!invoker_)
	{
		StopTargeting();
		return;
	}

	FVector target_location = GetGroundLocation();
	FVector origin = invoker_->GetActorLocation();
	FVector direction = target_location - origin;
	current_target_result_.target_location_ = target_location;


	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (game_mode)
	{
		if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Allies)
		{
			auto heroes = game_mode->GetHeroContainer();

			for (AActor* actor : heroes)
			{
				if (actor)
				{
					if (IsWithinSector(origin, direction, target_parameters_.range_, target_parameters_.radius_, actor->GetActorLocation()))
					{
						current_target_result_.target_actors_.Add(actor);
					}
				}
			}
		}
		if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Opponents)
		{
			auto enemies = game_mode->GetEnemyContainers();

			for (AActor* actor : enemies)
			{
				if (actor)
				{
					if (IsWithinSector(origin, direction, target_parameters_.range_, target_parameters_.radius_, actor->GetActorLocation()))
					{
						current_target_result_.target_actors_.Add(actor);
					}
				}
			}
		}
	}
	StopTargeting();
}

void UTargetingComponent::InitializeTargetingVisuals()
{
	AActor* owner = GetOwner();
	if (owner)
	{
		FActorSpawnParameters spawn_params;
		spawn_params.Owner = GetOwner();

		// Spawn an actor for visual aids
		// PlayerController itself does not have a visual child actors because they do not have body that have visuals.
		targeting_visual_actor_ = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, spawn_params);

		if (targeting_visual_actor_)
		{
			USceneComponent* root_component = NewObject<USceneComponent>(targeting_visual_actor_, TEXT("RootComponent"));
			targeting_visual_actor_->SetRootComponent(root_component);
			root_component->RegisterComponent();

			range_decal_ = NewObject<UDecalComponent>(targeting_visual_actor_);
			range_decal_->SetupAttachment(root_component);
			range_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
			range_decal_->SetVisibility(false);
			if (range_material_)
			{
				range_decal_->SetDecalMaterial(range_material_);
			}
			range_decal_->RegisterComponent();

			radius_decal_ = NewObject<UDecalComponent>(targeting_visual_actor_);
			radius_decal_->SetupAttachment(root_component);
			radius_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
			if (radius_material_)
			{
				radius_decal_->SetDecalMaterial(radius_material_);
			}
			radius_decal_->SetVisibility(false);
			radius_decal_->RegisterComponent();

			sector_decal_ = NewObject<UDecalComponent>(targeting_visual_actor_);
			sector_decal_->SetupAttachment(root_component);
			sector_decal_->SetVisibility(false);
			sector_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
			if (arc_material_)
			{
				sector_decal_->SetDecalMaterial(arc_material_);
			}
			sector_decal_->RegisterComponent();
		}

		highlight_dynamic_material_ = UMaterialInstanceDynamic::Create(highlight_material_, this);
	}
}

void UTargetingComponent::UpdateTargetingVisuals()
{
	FVector target_location = GetGroundLocation();
	FVector clamped_target_location = ClampingOntoInvoker(target_location);

	FVector invoker_location;
	if (invoker_)
	{
		invoker_location = invoker_->GetActorLocation();
	}
	else
	{
		// set its location to be logically invalid
		invoker_location = FVector(10000, 10000, 10000);
	}

	if (target_parameters_.current_mode_ == ETargetingMode::Actor)
	{
		range_decal_->SetWorldLocation(invoker_location);

		ApplyMaterialHighlight(FindClosestActor(target_location));
	}
	if (target_parameters_.current_mode_ == ETargetingMode::Location)
	{

		radius_decal_->SetWorldLocation(clamped_target_location);
		range_decal_->SetWorldLocation(invoker_location);
	}
	if (target_parameters_.current_mode_ == ETargetingMode::Direction)
	{
		sector_decal_->SetWorldLocation(invoker_location);

		FVector direction = clamped_target_location - invoker_location;
		FRotator target_rotation = UKismetMathLibrary::MakeRotFromZ(direction);
		sector_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
		sector_decal_->AddRelativeRotation(target_rotation);

		range_decal_->SetWorldLocation(invoker_location);
	}
}

void UTargetingComponent::CleanupTargetingVisuals()
{
	ApplyMaterialHighlight(nullptr);

	if (range_decal_)
	{
		range_decal_->SetVisibility(false);
	}
	if (radius_decal_)
	{
		radius_decal_->SetVisibility(false);
	}
	if (sector_decal_)
	{
		sector_decal_->SetVisibility(false);
	}
}

FVector UTargetingComponent::ProjectPointOntoCircle(const FVector& Point, const FVector& Origin, float Radius)
{
	FVector direction = Point - Origin;

	direction.Normalize();

	FVector result = Origin + direction * Radius;

	return result;
}

FVector UTargetingComponent::GetGroundLocation() const
{
	if (target_parameters_.is_self_targeting_)
	{
		if (invoker_)
		{
			invoker_->GetActorLocation();
		}
	}

	FHitResult hit_result;
	FVector world_location, world_direction;

	if (player_controller_->DeprojectMousePositionToWorld(world_location, world_direction))
	{
		FVector trace_end = world_location + (world_direction * 10000.f);
		FCollisionQueryParams query_params;
		query_params.AddIgnoredActor(GetOwner());

		if (GetWorld()->LineTraceSingleByChannel(hit_result, world_location, trace_end, ECC_Visibility, query_params))
		{
			return hit_result.Location;
		}
	}
	return FVector::ZeroVector;
}

FVector UTargetingComponent::ClampingOntoInvoker(const FVector& TargetLocation)
{
	// Check if location is within range
	if (invoker_)
	{
		FVector owner_location = invoker_->GetActorLocation();
		if (FVector::DistSquaredXY(owner_location, TargetLocation) >= target_parameters_.range_ * target_parameters_.range_)
		{
			return ProjectPointOntoCircle(TargetLocation, owner_location, target_parameters_.range_);
		}
	}

	return TargetLocation;
}

AActor* UTargetingComponent::FindClosestActor(const FVector& TargetLocation)
{
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!game_mode)
	{
		return nullptr;
	}
	if (target_parameters_.is_self_targeting_)
	{
		return invoker_;
	}

	AActor* closest_actor = nullptr;
	float closest_distance_sq = MAX_FLT;
	const float squared_range = target_parameters_.range_ * target_parameters_.range_;

	if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Allies)
	{
		auto characters = game_mode->GetHeroContainer();
		for (AActor* actor : characters)
		{
			if (actor)
			{
				if (IsActorInRange(actor, squared_range))
				{
					float distance_sq = FVector::DistSquared(TargetLocation, actor->GetActorLocation());
					if (distance_sq < closest_distance_sq)
					{
						closest_distance_sq = distance_sq;
						closest_actor = actor;
					}
				}
			}
		}
	}

	if (target_parameters_.target_type_ == ETargetType::All || target_parameters_.target_type_ == ETargetType::Opponents)
	{
		auto enemies = game_mode->GetEnemyContainers();
		for (AActor* actor : enemies)
		{
			if (actor)
			{
				if (IsActorInRange(actor, squared_range))
				{
					float distance_sq = FVector::DistSquared(TargetLocation, actor->GetActorLocation());
					if (distance_sq < closest_distance_sq)
					{
						closest_distance_sq = distance_sq;
						closest_actor = actor;
					}
				}
			}
		}

	}

	return closest_actor;
}

void UTargetingComponent::ApplyMaterialHighlight(AActor* target)
{

	if (previously_chosen_actor_ != target)
	{
		if (previously_chosen_actor_)
		{
			USkeletalMeshComponent* previous_mesh = previously_chosen_actor_->FindComponentByClass<USkeletalMeshComponent>();
			for (int32 i = 0; i < previous_mesh->GetNumMaterials(); i++)
			{
				previous_mesh->SetMaterial(i, original_materials_[i]);
			}
		}

		previously_chosen_actor_ = target;

		if (!target) return;

		// Store original materials
		USkeletalMeshComponent* MeshComponent = target->FindComponentByClass<USkeletalMeshComponent>();
		if (MeshComponent)
		{
			original_materials_.Empty();
			for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
			{
				original_materials_.Add(MeshComponent->GetMaterial(i));
			}

			// Apply highlight material to all slots
			for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
			{
				MeshComponent->SetMaterial(i, highlight_dynamic_material_);
			}
		}
	}
}

bool UTargetingComponent::IsWithinSector(const FVector& origin, const FVector& direction, float range, float angle, const FVector& actor_location)
{
	FVector to_actor = actor_location - origin;

	// Is the actor in range?
	float distance_to_actor = to_actor.SizeSquared();
	if (distance_to_actor > range * range)
	{
		return false;
	}

	FVector normalized_actor = to_actor.GetSafeNormal();
	FVector normalized_direction = direction.GetSafeNormal();

	float half_radian = FMath::DegreesToRadians(angle / 2.0);
	float cos_half_radian = FMath::Cos(half_radian);

	float dot_product = FVector::DotProduct(normalized_direction, normalized_actor);

	return dot_product >= cos_half_radian;
}

bool UTargetingComponent::IsActorInRange(AActor* actor, float squared_range)
{
	// return true if item selection mode is on (invoker is nullptr).
	return (invoker_ == nullptr) || (FVector::DistSquared(actor->GetActorLocation(), invoker_->GetActorLocation()) < squared_range);
}

void UTargetingComponent::StartFocus()
{
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (game_mode)
	{
		game_mode->SlowGlobalTimeDilation();
	}
}

void UTargetingComponent::EndFocus()
{
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (game_mode)
	{
		game_mode->RestoreGlobalTimeDilation();
	}
}