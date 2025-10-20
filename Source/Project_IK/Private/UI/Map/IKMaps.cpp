/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Map system.
					This file handles all actions about map.
					For example: procedurally generation of map, getter&setter, ...

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/Map/IKMaps.h"

#include "Subsystems/RandomNumberGeneratorSubsystem.h"

UIKMaps::UIKMaps()
	: Super::UObject()
{
}

void UIKMaps::GenerateMaps(int32 row, int32 col)
{
	// Reserve spaces in 2D arrays
	ClearMaps();
	map.SetNum(row);
	for (int32 i = 0; i < row; i++)
	{
		map[i].SetNum(col);
	}
	
	FRandomStream& rng = URandomNumberGeneratorSubsystem::GetRNG(GetWorld());
	rand_seed_for_map_ = rng.GetCurrentSeed();

	// The First Rooms randomly chosen at the 1rst Floor cannot be the same.
	int32 departures_num = FMath::CeilToInt(col / 2.f);
	TArray<int32> departures;
	while (departures.Num() < departures_num)
	{
		int32 d = rng.RandRange(0, col - 1);
		departures.AddUnique(d);
	}
	departures.Sort();

	// then connects it with a Path to one of the 3 closest Rooms on the 2nd Floor. 
	for (int32 i = 0; i < departures_num; i++)
	{
		const int32 c = departures[i];
		int32 paths = FMath::Min(FMath::CeilToInt32(rng.FRandRange(0.f, 1.1f)), AvaiableBranchNum(0, c));
		map[0][c].type = QueryNodeType();
		while (map[0][c].next.Num() < paths)
		{
			int32 next = FMath::Clamp(c + rng.RandRange(-1, 1), 0, col - 1);
			if (!IsPathCrossed(0, c, next))
			{
				map[0][c].next.AddUnique(next);
			}
		}
	}

	// repeats this procces until reaches to the top floor before Boss
	for (int32 i = 0; i < row - 3; i++)
	{
		for (int32 j = 0; j < col; j++)
		{
			if (map[i][j].type != NodeType::None)
			{
				for (int32 t = 0; t < map[i][j].next.Num(); t++)
				{
					const int32 target = map[i][j].next[t];
					FMapNode& node = map[i + 1][target];
					node.type = QueryNodeType();

					int32 old_path_num = node.next.Num();

					int32 new_path_num = FMath::Min(FMath::CeilToInt32(rng.FRandRange(0.f, 1.1f)) + old_path_num, AvaiableBranchNum(i + 1, target));
					while (old_path_num < new_path_num)
					{
						int32 next = FMath::Clamp(target + rng.RandRange(-1, 1), 0, col - 1);
						// If it is invalid path, consider path adding has been done. Did not add though
						if (!IsPathCrossed(i + 1, target, next))
						{
							map[i + 1][target].next.AddUnique(next);
							++old_path_num;
						}
					}
				}
			}
		}
	}

	// Set NodeType on the top floor nodes.
	for (size_t i = 0; i < col; i++)
	{
		for (int32 t = 0; t < map[row - 3][i].next.Num(); t++)
		{
			const int32 target = map[row - 3][i].next[t];
			map[row - 2][target].type = QueryNodeType();
			// Connect top floor nodes to the Boss node.
			map[row - 2][target].next.AddUnique(0);
		}
	}

	// Set Boss node
	map[row - 1][0].type = NodeType::Boss;

	CorrectInvalidNodes();
}

const FMapNode& UIKMaps::GetNode(int32 row, int32 col) const
{
	return map[row][col];
}

const FMapNode& UIKMaps::GetNode(FIntPoint int_point) const
{
	return map[int_point.X][int_point.Y];
}

void UIKMaps::SetNode(int32 row, int32 col, const FMapNode& node)
{
	map[row][col] = node;
}

void UIKMaps::SetPlayerGridPosition(FIntPoint position)
{
	player_visited_path_.Add(position);

	player_grid_position_ = position;
}

FIntPoint UIKMaps::GetPlayerGridPosition() const
{
	return player_grid_position_;
}

const TArray<FIntPoint>& UIKMaps::GetPlayerVisitedPath() const
{
	return player_visited_path_;
}

int32 UIKMaps::GetRandSeedForMap() const
{
	return rand_seed_for_map_;
}

void UIKMaps::RecoverMaps(int32 rand_seed_for_map, int32 map_height, int32 map_width, const TArray<FIntPoint>& player_visited_path)
{
	URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).Initialize(rand_seed_for_map);
	GenerateMaps(map_height, map_width);

	player_visited_path_ = player_visited_path;
	if (player_visited_path_.IsEmpty() == false)
	{
		player_grid_position_ = player_visited_path_.Top();
	}
}

void UIKMaps::ClearMaps()
{
	for (int32 i = 0; i < map.Num(); i++)
	{
		map[i].Empty();
	}
	map.Empty();

	player_grid_position_ = FIntPoint(-1);
	player_visited_path_.Empty();
}

bool UIKMaps::IsPathCrossed(int32 row, int32 col, int32 path_to) const
{
	// Impossible to be crossed when path points to top.
	if (col == path_to)
	{
		return false;
	}
	// Check right node when path points to right
	else if (path_to > col)
	{
		return map[row][col + 1].next.Contains(col);
	}
	// Check left node when path points to left
	else
	{
		return map[row][col - 1].next.Contains(col);
	}
}

NodeType UIKMaps::QueryNodeType(const TArray<NodeType>& excluded_types) const
{
	TArray<NodeType> return_types = { NodeType::Enemy, NodeType::Merchant, NodeType::Event };

	return_types.RemoveAll([&](NodeType type)
		{
			return excluded_types.Contains(type);
		});

	if (return_types.Num() <= 0)
	{
		return NodeType::Enemy;
	}

	int32 rand = URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).RandRange(0, return_types.Num() - 1);
	return return_types[rand];
}

int32 UIKMaps::AvaiableBranchNum(int32 row, int32 col) const
{
	// The maximum number of branch : It is 3 because it connects to one of the 3 closest.
	static constexpr int32 MAX_BRANCH_NUM = 3;

	// If the node is the most left node, only two possible connection available.
	if (col <= 0)
	{
		return MAX_BRANCH_NUM - 1;
	}

	int32 modifier = 0;
	// If the node is the most right node, one branch became impossible to connect.
	if (col >= GetWidth() - 1)
	{
		modifier += 1;
	}

	// If the node is able to be crossed, one branch became impossible to connect.
	if (map[row][col - 1].next.Contains(col))
	{
		modifier += 1;
	}

	return MAX_BRANCH_NUM - modifier;
}

// This function reassigning node to obey the below rules.
	// 1. Merchant and Event nodes cannot be assigned below the 2th Floor.
	// 4. All nodes before the Boss should be *Enemy* node.
	// 2. Merchant and Event nodes cannot be consecutive.
	// 3. A Room that that has 2 or more Paths going out 
		// must have all destinations be unique. 
		// 2 destinations originating form the same Room 
		// cannot share the same Location.

void UIKMaps::CorrectInvalidNodes()
{
	const int32 width = GetWidth();
	const int32 height = GetHeight();

	// Do not correct boss node.
	for (int32 row = 0; row < height - 1; ++row)
	{
		for (int32 col = 0; col < width; ++col)
		{
			if (map[row][col].type == NodeType::None)
			{
				continue;
			}
			ApplyRule1(row, col);
			ApplyRule4(row, col);
			ApplyRule2(row, col);
			ApplyRule3(row, col);
		}
	}
}

// 1. Merchant and Event nodes can��t be assigned below the 2th Floor.
void UIKMaps::ApplyRule1(int32 row, int32 col)
{
	if (row <= 2)
	{
		if (map[row][col].type == NodeType::Merchant || map[row][col].type == NodeType::Event)
		{
			map[row][col].type = QueryNodeType({ NodeType::Merchant , NodeType::Event });
		}
	}
}

// 2. Merchant and Event nodes cannot be consecutive.
void UIKMaps::ApplyRule2(int32 row, int32 col)
{
	if (map[row][col].type == NodeType::Merchant || map[row][col].type == NodeType::Event)
	{
		for (const int32 n : map[row][col].next)
		{
			if (map[row][col].type == map[row + 1][n].type)
			{
				map[row + 1][n].type = QueryNodeType({map[row][col].type});
			}
		}
	}
}

// 3. A Room that that has 2 or more Paths going out 
	// must have all destinations be unique. 
	// 2 destinations originating form the same Room 
	// cannot share the same Location.
void UIKMaps::ApplyRule3(int32 row, int32 col)
{
	if (map[row][col].next.Num() >= 2)
	{
		TArray<NodeType> destination_types({ map[row][col].type });
		for (const int32 n : map[row][col].next)
		{
			NodeType type = map[row + 1][n].type;
			if (destination_types.Contains(type))
			{
				NodeType new_type = QueryNodeType(destination_types);
				map[row + 1][n].type = new_type;
			}
			destination_types.Add(map[row + 1][n].type);
		}
	}
}

// 4. All nodes before the Boss should be *Enemy* node.
// It can be changed probably like a "Rest" node.
void UIKMaps::ApplyRule4(int32 row, int32 col)
{
	if (row >= GetHeight() - 2)
	{
		map[row][col].type = NodeType::Enemy;
	}
}
