#include "stdafx.h"
#include "DungeonGenerator.h"
#include "Map.h"

DungeonGenerator::DungeonGenerator()
{
}

Map* DungeonGenerator::GenerateMap(int p_iWidth, int p_iHeight, int p_iDensity, int p_iSeed)
{
	std::printf("Creating dungeon with width %i, height %i and density %i \n", p_iWidth, p_iHeight, p_iDensity);
	Map* dungeon = new Map(p_iWidth, p_iHeight);
	std::srand(p_iSeed);
	std::rand();

	std::vector<SDL_Rect> rooms;

	for (int i = 0; i < p_iDensity; i++)
	{
		SDL_Rect newRoom;
		newRoom.h = 3 + (rand() % 8);
		newRoom.w = 3 + (rand() % 8);
		newRoom.x = 1 + (rand() % (p_iWidth - newRoom.w));
		newRoom.y = 1 + (rand() % (p_iHeight - newRoom.h));

		if (i == 0)
		{
			rooms.push_back(newRoom);
			continue;
		}

		auto it = rooms.begin();
		bool valid = true;
		while (it != rooms.end() && valid)
		{
			if (AABB((*it), newRoom))
			{
				valid = false;
			}
			it++;
		}

		if (valid)
		{
			rooms.push_back(newRoom);
		}
	}

	std::printf("Successfully created %i rooms.\n", rooms.size());
	auto it = rooms.begin();
	while (it != rooms.end())
	{
		
		for (int y = 0; y < (*it).h; y++)
		{
			for (int x = 0; x < (*it).w; x++)
			{
				dungeon->SetTile(x + (*it).x, y + (*it).y, '.');
			}
		}
		it++;
	}

	// TODO: Find a more efficient way to do this.
	// Jag menar, 4st nästlade for-loops? Det måste fan finnas ett bättre sätt.
	for (int x = 1; x < p_iWidth - 1; x++)
	{
		for (int y = 1; y < p_iHeight - 1; y++)
		{
			bool enclosed = true;
			for (int dx = -1; dx <= 1 && enclosed; dx++)
			{
				for (int dy = -1; dy <= 1 && enclosed; dy++)
				{
					if (dungeon->GetTile(x + dx, y + dy) == '.')
					{
						enclosed = false;
					}
				}
			}

			if (enclosed)
			{
				MazeGen(x, y, dungeon);
			}

		}
	}
	/*
	it = rooms.begin();
	while (it != rooms.end())
	{
		for (int i = 0; i < (*it).h; i++)
		{//197 1
			if (dungeon->GetTile((*it).x - 2, (*it).y + i) == '.')
			{
				dungeon->SetTile((*it).x - 1, (*it).y + i, 1);
			}
			if (dungeon->GetTile((*it).x + (*it).w + 1, (*it).y + i) == '.')
			{
				dungeon->SetTile((*it).x + (*it).w, (*it).y + i, 1);
			}
		}

		for (int i = 0; i < (*it).w; i++)
		{
			if (dungeon->GetTile((*it).x + i, (*it).y - 2) == '.')
			{
				dungeon->SetTile((*it).x + i, (*it).y - 1, 1);
			}
			if (dungeon->GetTile((*it).x + i, (*it).y + (*it).h + 1) == '.')
			{
				dungeon->SetTile((*it).x + i, (*it).y + (*it).h, 1);
			}
		}

		it++;
	}
	*/
	return dungeon;
}

bool DungeonGenerator::AABB(SDL_Rect left, SDL_Rect right)
{
	// Standard AABB, except we're adding 1 to the widths/heights to make sure there's space for walls between rooms
	if (left.x < right.x + right.w +1 && left.x + left.w +1 > right.x &&
		left.y < right.y + right.h +1 && left.y + left.h +1 > right.y)
	{
		return true;
	}

	return false;
}

void DungeonGenerator::MazeGen(int p_iX, int p_iY, Map* p_pxMap)
{
	p_pxMap->SetTile(p_iX, p_iY, '.');

	std::vector<int> dirs; // Available directions from this position, stored in "numpad-format". Look at your numpad and then the number and you'll get it.

	if (p_pxMap->GetTile(p_iX - 1, p_iY) != '.') // Left
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (p_pxMap->GetTile(p_iX - 1, p_iY - 1 + i) == '.')
			{
				enclosed = false;
			}
			if (p_pxMap->GetTile(p_iX - 2, p_iY - 1 + i) == '.')
			{
				enclosed = false;
			}
		}
		if (enclosed) 
		{
			dirs.push_back(4);
		}
	}
	
	if (p_pxMap->GetTile(p_iX + 1, p_iY) != '.') // Right
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (p_pxMap->GetTile(p_iX + 1, p_iY - 1 + i) == '.')
			{
				enclosed = false;
			}
			if (p_pxMap->GetTile(p_iX + 2, p_iY - 1 + i) == '.')
			{
				enclosed = false;
			}
		}
		if (enclosed)
		{
			dirs.push_back(6);
		}
	}

	if (p_pxMap->GetTile(p_iX, p_iY - 1) != '.') // Up
	{
		bool enclosed = true;
		for (int i = -1; i <= 1 && enclosed; i++)
		{
			if (p_pxMap->GetTile(p_iX + i, p_iY - 1) == '.')
			{
				enclosed = false;
			}
			if (p_pxMap->GetTile(p_iX + i, p_iY - 2) == '.')
			{
				enclosed = false;
			}
		}
		if (enclosed)
		{
			dirs.push_back(8);
		}
	}

	if (p_pxMap->GetTile(p_iX, p_iY + 1) != '.') // Down
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (p_pxMap->GetTile(p_iX - 1 + i, p_iY + 1) == '.')
			{
				enclosed = false;
			}
			if (p_pxMap->GetTile(p_iX - 1 + i, p_iY + 2) == '.')
			{
				enclosed = false;
			}
		}
		if (enclosed)
		{
			dirs.push_back(2);
		}
	}

	if (dirs.size() != 0)
	{
		switch (dirs.at(std::rand() % dirs.size()))
		{
		case 4: // Left
			MazeGen(p_iX - 1, p_iY, p_pxMap);
			break;
		case 6: // Right
			MazeGen(p_iX + 1, p_iY, p_pxMap);
			break;
		case 8: // Up
			MazeGen(p_iX, p_iY - 1, p_pxMap);
			break;
		case 2: // Down
			MazeGen(p_iX, p_iY + 1, p_pxMap);
			break;
		default:
			break;
		}
		MazeGen(p_iX, p_iY, p_pxMap); // Check once again to check if there's any directions to go from here
	}
	else 
	{
		return;
	}
}
