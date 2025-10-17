/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Map system.
					This file handles all actions about map.
					For example: procedurally generation of map, getter&setter, ...

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Managers/EnumCluster.h"
#include "IKMaps.generated.h"

enum class NodeType : uint8;

USTRUCT(BlueprintType)
struct FMapNode
{
	GENERATED_BODY()

	FMapNode()
		:type(NodeType::None)
	{}

	UPROPERTY(VisibleAnywhere, Category="MapNode")
	NodeType type;
	UPROPERTY(VisibleAnywhere, Category = "MapNode")
	TArray<int32> next;
};

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UIKMaps : public UObject
{
	GENERATED_BODY()
	
public:
	UIKMaps();

	// Call the function with at least 3 level of rows.
	UFUNCTION(BlueprintCallable, Category="Map")
	void GenerateMaps(int32 row, int32 col);
	UFUNCTION(BlueprintCallable, Category="Map")
	inline int32 GetMaxNode() const
	{
		return GetWidth() * GetHeight();
	}
	// Col
	UFUNCTION(BlueprintCallable, Category = "Map")
	inline int32 GetWidth() const
	{
		return map[0].Num();
	}
	// Row
	UFUNCTION(BlueprintCallable, Category = "Map")
	inline int32 GetHeight() const
	{
		return map.Num();
	}
	UFUNCTION(BlueprintCallable, Category = "Map")
	const FMapNode& GetNode(int32 row, int32 col) const;
	const FMapNode& GetNode(FIntPoint int_point) const;
	void SetNode(int32 row, int32 col, const FMapNode& node);

	void SetPlayerGridPosition(FIntPoint position);
	FIntPoint GetPlayerGridPosition() const;

	const TArray<FIntPoint>& GetPlayerVisitedPath() const;

	int32 GetRandSeedForMap() const;

	void RecoverMaps(int32 rand_seed_for_map, int32 map_height, int32 map_width, const TArray<FIntPoint>& player_visited_path);

protected:
	TArray<TArray<FMapNode>> map;
	FIntPoint player_grid_position_;

	TArray<FIntPoint> player_visited_path_;

	int32 rand_seed_for_map_ = 0;

	void ClearMaps();
	bool IsPathCrossed(int32 row, int32 col, int32 path_to) const;
	NodeType QueryNodeType(const TArray<NodeType>& excluded_types = {}) const;
	int32 AvaiableBranchNum(int32 row, int32 col) const;
	void CorrectInvalidNodes();
	void ApplyRule1(int32 row, int32 col);
	void ApplyRule2(int32 row, int32 col);
	void ApplyRule3(int32 row, int32 col);
	void ApplyRule4(int32 row, int32 col);
};