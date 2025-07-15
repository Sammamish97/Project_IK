/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.11.2025
Summary : Header file for a subsystem that manages global buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Structs/GlobalBuff.h"
#include "GlobalBuffSubsystem.generated.h"

enum class EGlobalBuffType : uint8;
class UGlobalBuffLogicBase;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGlobalBuffSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddBuff(EGlobalBuffType buff_type);
	bool RemoveBuff(EGlobalBuffType buff_type);

	void ApplyBuff(UObject* buff_target);

	bool HasBuff(EGlobalBuffType buff_type);

	void ClearBuffs();

	void UpdateBuffDurations();

	const TArray<FGlobalBuffData>& GetBuffs() const;

	void AddEverlastingBuff(EGlobalBuffType buff_type);

	// Naively implement for sake of implementation of displaying everlasting buffs rapidly.
	const TSet<EGlobalBuffType> GetEverlastingBuffTypes() const;

protected:
	TMap<EGlobalBuffType, int32> buff_lookup_;
	TMap<EGlobalBuffType, int32> newly_added_buff_lookup_;

	// Self curious -> No need to contain it?
	TArray<FGlobalBuffData> buffs_;

	UPROPERTY()
	TMap<EGlobalBuffType, TObjectPtr<UGlobalBuffLogicBase>> buff_logic_containers_;

	TSet<EGlobalBuffType> everlasting_buff_;
};
