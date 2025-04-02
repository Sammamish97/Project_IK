/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.27.2025
Summary : Header file for a subsystem that manages delegate bindings.
					Need to use this class to construct bindings for sake of LOOSE COUPLING

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "WorldSettings/IKPlayerController.h"
#include "Components/TargetingComponent.h"
#include "Characters/Unit.h"
#include "Components/CrowdControlComponent.h"
#include "Components/CharacterStatComponent.h"

#include "DelegateBridgeSubsystem.generated.h"

#define BindOnTargetingCanceled(Object, FuncName) \
	__Internal_BindOnTargetingCanceled(Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnItemUsed(Object, FuncName) \
	__Internal_BindOnItemUsed(Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnActiveSkill(Object, FuncName) \
	__Internal_BindOnActiveSkill(Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnCrowdControlChanged(Component, Object, FuncName) \
	__Internal_BindOnCrowdControlChanged(Component, Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnDied(Component, Object, FuncName) \
	__Internal_BindOnDied(Component, Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnHPChanged(Component, Object, FuncName) \
	__Internal_BindOnHPChanged(Component, Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnShieldChanged(Component, Object, FuncName) \
	__Internal_BindOnShieldChanged(Component, Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

#define BindOnBuffChanged(Component, Object, FuncName) \
	__Internal_BindOnBuffChanged(Component, Object, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) )  )

/**
 *
 */
UCLASS()
class PROJECT_IK_API UDelegateBridgeSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	template<typename T, typename FuncType>
	bool __Internal_BindOnTargetingCanceled(T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnItemUsed(T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnActiveSkill(T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool BindOnUnitDamageEvent(UObject* bound_unit, EUnitEvent bound_event, T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnCrowdControlChanged(UObject* bound_crowd_control_component, T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnDied(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnHPChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnShieldChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name);

	template<typename T, typename FuncType>
	bool __Internal_BindOnBuffChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name);

protected:
	AIKPlayerController* GetAIKPlayerController() const;
};

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnTargetingCanceled(T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnTargetingCanceled:: Object is null"));
		return false;
	}

	AIKPlayerController* pc = GetAIKPlayerController();
	if (pc != nullptr)
	{
		UTargetingComponent* targeting_component = pc->GetTargetingComponent();
		if (targeting_component != nullptr)
		{
			targeting_component->OnTargetingCanceled.__Internal_AddUniqueDynamic(object, callback, func_name);
			return true;
		}
	}

	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnItemUsed(T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnItemUsed:: Object is null"));
		return false;
	}
	AIKPlayerController* pc = GetAIKPlayerController();
	if (pc != nullptr)
	{
		pc->on_item_used_.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnActiveSkill(T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnItemUsed:: Object is null"));
		return false;
	}
	AIKPlayerController* pc = GetAIKPlayerController();
	if (pc)
	{
		pc->on_active_skill_.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::BindOnUnitDamageEvent(UObject* bound_actor, EUnitEvent bound_event, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_actor != nullptr && bound_actor->IsA<AUnit>())
	{
		AUnit* bound_unit = Cast<AUnit>(bound_actor);
		TArray<FOnDamage>& delegate_array = bound_unit->dmg_event_map_.FindOrAdd(bound_event);

		delegate_array.AddDefaulted();
		delegate_array.Last().BindUObject(object, callback);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnCrowdControlChanged(UObject* bound_crowd_control_component, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_crowd_control_component != nullptr && bound_crowd_control_component->IsA<UCrowdControlComponent>())
	{
		UCrowdControlComponent* cc = Cast<UCrowdControlComponent>(bound_crowd_control_component);
		cc->OnCrowdControlChanged.__Internal_AddUniqueDynamic(object, callback, func_name);
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnDied(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_character_stat_component != nullptr && bound_character_stat_component->IsA<UCharacterStatComponent>())
	{
		UCharacterStatComponent* cs = Cast<UCharacterStatComponent>(bound_character_stat_component);
		cs->OnDied.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnHPChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_character_stat_component != nullptr && bound_character_stat_component->IsA<UCharacterStatComponent>())
	{
		UCharacterStatComponent* cs = Cast<UCharacterStatComponent>(bound_character_stat_component);
		cs->OnHPChanged.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnShieldChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_character_stat_component != nullptr && bound_character_stat_component->IsA<UCharacterStatComponent>())
	{
		UCharacterStatComponent* cs = Cast<UCharacterStatComponent>(bound_character_stat_component);
		cs->OnShieldChanged.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}

template<typename T, typename FuncType>
inline bool UDelegateBridgeSubsystem::__Internal_BindOnBuffChanged(UObject* bound_character_stat_component, T* object, FuncType callback, FName func_name)
{
	if (object == nullptr)
	{
		return false;
	}
	if (bound_character_stat_component != nullptr && bound_character_stat_component->IsA<UCharacterStatComponent>())
	{
		UCharacterStatComponent* cs = Cast<UCharacterStatComponent>(bound_character_stat_component);
		cs->OnBuffChanged.__Internal_AddUniqueDynamic(object, callback, func_name);
		return true;
	}
	return false;
}
