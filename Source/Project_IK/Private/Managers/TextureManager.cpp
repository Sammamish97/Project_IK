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

//UTexture2D* UTextureManager::GetTexture(const FString& Key) const
//{
//	if (textures_.Contains(Key))
//	{
//		TSoftObjectPtr<UTexture2D> soft_texture = textures_[Key];
//		// In the case you want it to be asynchronously, call LoadAssetAsync with 
//		// a passed callback function that takes pointer to UTexture2D.
//		return soft_texture.LoadSynchronous();
//	}
//	return nullptr;
//}

void UTextureManager::GetAllTexturesInFolder(const FString& FolderPath)
{
	FAssetRegistryModule& asset_registry_module = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter filter;
	filter.PackagePaths.Add(*FolderPath);
	// Include subfolders
	filter.bRecursivePaths = true;
	// Ensures retrieving only texture assets.
	filter.ClassPaths.Add(UTexture2D::StaticClass()->GetClassPathName());

	TArray<FAssetData> asset_data_list;
	asset_registry_module.Get().GetAssets(filter, asset_data_list);

	for (const FAssetData& data : asset_data_list)
	{
		TSoftObjectPtr<UTexture2D> soft_texture(data.ToSoftObjectPath());
		textures_.Add(data.AssetName.ToString(), soft_texture);
	}
}
