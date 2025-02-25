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


#include "UI/IKMaps.h"

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

	// The First Rooms randomly chosen at the 1rst Floor cannot be the same.
	int32 departures_num = FMath::CeilToInt(col / 2.f);
	TArray<int32> departures;
	while (departures.Num() < departures_num)
	{
		int32 d = FMath::RandRange(0, col - 1);
		departures.AddUnique(d);
	}

	// then connects it with a Path to one of the 3 closest Rooms on the 2nd Floor. 
	for (int32 i = 0; i < departures_num; i++)
	{
		const int32 c = departures[i];
		int32 paths = FMath::Min(FMath::CeilToInt32(FMath::RandRange(0.f, 1.1f)), AvaiableBranchNum(0, c));
		map[0][c].type = QueryNodeType();
		while (map[0][c].next.Num() < paths)
		{
			int32 next = FMath::Clamp(c + FMath::RandRange(-1, 1), 0, col - 1);
			if (!IsPathCrossed(0, c, next))
			{
				map[0][c].next.AddUnique(next);
			}
		}
	}

	// repeats this procces until reaches to the top floor
	for (int32 i = 0; i < row - 2; i++)
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

					int32 new_path_num = FMath::Min(FMath::CeilToInt32(FMath::RandRange(0.f, 1.1f)) + old_path_num, AvaiableBranchNum(i + 1, target));
					while (old_path_num < new_path_num)
					{
						int32 next = FMath::Clamp(target + FMath::RandRange(-1, 1), 0, col - 1);
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

	// Set only NodeType on the top floor nodes
	for (size_t i = 0; i < col; i++)
	{
		for (int32 t = 0; t < map[row - 2][i].next.Num(); t++)
		{
			const int32 target = map[row - 2][i].next[t];
			map[row - 1][target].type = QueryNodeType();
		}
	}
}

const FMapNode& UIKMaps::GetNode(int32 row, int32 col) const
{
	return map[row][col];
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

TArray<FIntPoint> UIKMaps::GetPlayerVisitedPath() const
{
	return player_visited_path_;
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

NodeType UIKMaps::QueryNodeType() const
{
	return NodeType::Enemy;
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
