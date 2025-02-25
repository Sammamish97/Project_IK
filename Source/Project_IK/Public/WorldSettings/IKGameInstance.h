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

#include "Managers/DataTableManager.h"

#include "IKGameInstance.generated.h"

class UItemInventory;
class UIKMaps;
class UCharacterDataManager;
class UItemDataManager;
class ULevelTransitionManager;
class UTextureManager;
class UDialogueEventManager;

UCLASS(Blueprintable)
class PROJECT_IK_API UIKGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UIKGameInstance();

	virtual void Init() override;

	UFUNCTION(BlueprintPure)
	const class UItemDataManager* GetItemDataManager() noexcept;
	UFUNCTION(BlueprintPure)
	class UItemInventory* GetItemInventory() const noexcept;
	UFUNCTION(BlueprintPure)
	class UIKMaps* GetMapPtr() const noexcept;
	UFUNCTION(BlueprintPure)
	const class UDronePluginManager* GetDronePluginManager() noexcept;
	UFUNCTION(BlueprintPure)
	const class UTextureManager* GetTextureManager() const noexcept;
	UFUNCTION(BlueprintPure)
	const class UDialogueEventManager* GetDialogueEventManager() const noexcept;
	UFUNCTION(BlueprintPure)
	class UInventoryManager* GetInventoryManager() const noexcept;
	UFUNCTION(BlueprintPure)
	class ULevelTransitionSubsystem* GetLevelTransitionSubsystem() const noexcept;
	UFUNCTION(BlueprintPure)
	UDataTableManager* GetDataTableManager() const noexcept;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTransition")
	TSubclassOf<AActor> hero_blueprint_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelTransition")
	TSubclassOf<AActor> enemy_blueprint_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInventory")
	TSubclassOf<UItemInventory> item_inventory_class_;

private:
	void InitializeItemDataManager();
	void InitializeCharacterDataManager();
	void InitializeItemInventory();
	void InitializeMaps();
	void InitializeDronePluginManager();
	void InitializeTextureManager();
	void InitializeDialogueEventManager();
	void InitInventoryManager();
	void InitDataTableManager();
	
	UPROPERTY()
	class UItemDataManager* item_data_manager_;

	UPROPERTY()
	class UItemInventory* item_inventory_;

	UPROPERTY()
	class UIKMaps* maps_;
	
	UPROPERTY()
	class UDronePluginManager* drone_plugin_manager_;

	UPROPERTY()
	class UDialogueEventManager* dialogue_event_manager_;

	UPROPERTY()
	class UTextureManager* texture_manager_;

	UPROPERTY()
	class UInventoryManager* inventory_manager_;

	TObjectPtr<UDataTableManager> data_table_manager_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance", meta = (AllowPrivateAccess = "true", BindWidget))
	TSubclassOf<UDataTableManager> data_table_class_;
};
