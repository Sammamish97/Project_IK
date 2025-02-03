/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.05.2024
Summary : Source file for texture manager.
					It loads all textures using in the game at the beginning of the game.
					Provide when codes needed.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/TextureManager.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "Components/CharacterStatComponent.h"

void UTextureManager::InitializeTextures()
{
	GetAllTexturesInFolder("/Game/Images");
}

UTexture2D* UTextureManager::GetTexture(FString Key) const
{
	if (textures_.Contains(Key))
	{
		return textures_[Key];
	}
	return nullptr;
}

UTexture2D* UTextureManager::GetBuffTexture(ECharacterStatType StatType) const
{
	switch (StatType)
	{
	case ECharacterStatType::AttackPower:
		break;
	case ECharacterStatType::AttackSpeed:
		return textures_["fire_rate_burst"];
		break;
	case ECharacterStatType::CriticalHitRate:
		break;
	case ECharacterStatType::Accuracy:
		break;
	case ECharacterStatType::MagazineBonus:
		break;
	case ECharacterStatType::LifeSteal:
		break;
	case ECharacterStatType::HitPoints:
		break;
	case ECharacterStatType::EvasionRate:
		return textures_["evasion"];
		break;
	case ECharacterStatType::Armor:
		break;
	case ECharacterStatType::Survivability:
		break;
	case ECharacterStatType::MoveSpeed:
		return textures_["move_speed"];
		break;
	case ECharacterStatType::ActiveSkillPower:
		break;
	case ECharacterStatType::ActiveSkillCooldown:
		break;
	case ECharacterStatType::PassiveSkillPower:
		break;
	case ECharacterStatType::PassiveSkillCooldown:
		break;
	case ECharacterStatType::Shield:
		break;
	default:
		break;
	}
	return nullptr;
}

UTexture2D* UTextureManager::GetCCTexture(ECCType CCType) const
{
	switch (CCType)
	{
	case ECCType::DroneJamming:
		return textures_["drone_jamming"];
		break;
	case ECCType::Silence:
		return textures_["silence"];
		break;
	case ECCType::MuteItems:
		return textures_["mute_items"];
		break;
	case ECCType::Stun:
		return textures_["stun"];
		break;
	default:
		break;
	}
	return nullptr;
}

void UTextureManager::GetAllTexturesInFolder(const FString& FolderPath)
{
	FAssetRegistryModule& asset_registry_module = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	if (!asset_registry_module.Get().IsLoadingAssets())
	{
		asset_registry_module.Get().SearchAllAssets(true);
	}

	FARFilter filter;
	filter.PackagePaths.Add(*FolderPath);
	// Include subfolders
	filter.bRecursivePaths = true;

	TArray<FAssetData> asset_data_list;
	asset_registry_module.Get().GetAssets(filter, asset_data_list);

	for (const FAssetData& data : asset_data_list)
	{
		// Synchronously load the texture asset
		UTexture2D* texture = Cast<UTexture2D>(data.GetAsset());
		if (texture)
		{
			textures_.Add(texture->GetName(), texture);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load texture: %s"), *data.ObjectPath.ToString());
		}
	}
}
