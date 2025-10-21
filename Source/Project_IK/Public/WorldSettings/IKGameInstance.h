/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.19.2024
Summary : Header file for Game Instance. It is used to initialize game app.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IKGameInstance.generated.h"

class UPauseManager;
class UTextManager;
class USetBonusManager;
class UIKMaps;
class UCharacterDataManager;
class UInventoryManager;
class UPerkEffectBase;
struct FPerkNode;
enum class ECharacterStatType : uint8;

UCLASS(Blueprintable)
class PROJECT_IK_API UIKGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UIKGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	void ClearRunData();

	UFUNCTION(BlueprintPure)
	class UIKMaps* GetMapPtr() const noexcept;
	UFUNCTION(BlueprintPure)
	class UInventoryManager* GetInventoryManager() const noexcept;
	UFUNCTION(BlueprintPure)
	class ULevelTransitionSubsystem* GetLevelTransitionSubsystem() const noexcept;
	UFUNCTION(BlueprintPure)
	UDataTableManager* GetDataTableManager() const noexcept;
	UFUNCTION(BlueprintPure)
	UTextManager* GetTextManager() const noexcept;

	void EnhanceHeroesStatData(ECharacterStatType stat_type, float increase_amount);
	void DiminishHeroesStatData(ECharacterStatType stat_type, float decrease_amount);

	const TArray<FPerkNode>& GetTree() const;
	
	UFUNCTION(BlueprintPure)
	USetBonusManager* GetSetBonusManager() const noexcept;
	UFUNCTION(BlueprintPure)
	class UEventManager* GetEventManager() const noexcept;

	void LoadRunSaveData();

	bool IsFirstBattle();
	bool IsFirstInventory();

	void SetIsFirstBattleFalse();
	void SetIsFirstInventoryFalse();
private:
	void InitializePerkEffectsAlreadyUnlocked();
	void InitializeMaps();
	void InitInventoryManager();
	void InitDataTableManager();
	void InitSpawnData();
	void InitSetBonusManager();
	void InitEventManager();
	void InitTextManager();
	void LoadSaveData();
	
	UPROPERTY()
	TObjectPtr<UIKMaps> maps_;

	UPROPERTY()
	TObjectPtr<UDataTableManager> data_table_manager_;
	
	UPROPERTY()
	TObjectPtr<USetBonusManager> set_bonus_manager_;

	UPROPERTY()
	TObjectPtr<UEventManager> event_manager_;
	
	UPROPERTY()
	TObjectPtr<UInventoryManager> inventory_manager_;

	UPROPERTY()
	TObjectPtr<UTextManager> text_manager_;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDataTableManager> data_table_class_;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USetBonusManager> set_bonus_class_;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UEventManager> event_manager_class_;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryManager> inventory_manager_class_;

	UPROPERTY(EditDefaultsOnly, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UTextManager> text_manager_class_;
};
