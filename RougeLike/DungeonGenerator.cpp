#include "stdafx.h"
#include "DungeonGenerator.h"
#include "TileManager.h"
#include "TileMap.h"

DungeonGenerator::DungeonGenerator()
{
}

TileMap* DungeonGenerator::GenerateMap(int p_iWidth, int p_iHeight, int p_iDensity, int p_iSeed)
{
	std::printf("Creating dungeon with width %i, height %i and density %i \n", p_iWidth, p_iHeight, p_iDensity);
	TileMap* dungeon = new TileMap(p_iWidth, p_iHeight);
	std::srand(p_iSeed);
	std::rand();

	Tile wallTile;
	wallTile.spriteId = '#';
	wallTile.r = 200;
	wallTile.g = 200;
	wallTile.b = 200;
	wallTile.description = "A brick wall. Pretty sturdy.";
	wallTile.isSolid = true;
	wallTile.blocksSight = true;

	Tile floorTile;
	floorTile.spriteId = '.';
	floorTile.r = 200;
	floorTile.g = 200;
	floorTile.b = 200;
	floorTile.description = "It's the floor. You know, the thing you walk on.";
	floorTile.blocksSight = false;
	floorTile.isSolid = false;

	Tile entranceTile;
	entranceTile.spriteId = '<';
	entranceTile.r = 200;
	entranceTile.g = 200;
	entranceTile.b = 200;
	entranceTile.description = "A stairway leading upwards.";
	entranceTile.blocksSight = false;
	entranceTile.isSolid = false;

	Tile exitTile;
	exitTile.spriteId = '>';
	exitTile.r = 200;
	exitTile.g = 200;
	exitTile.b = 200;
	exitTile.description = "A stairway leading downwards.";
	exitTile.blocksSight = false;
	exitTile.isSolid = false;

	Tile doorTile;
	doorTile.spriteId = '+';
	doorTile.r = 112;
	doorTile.g = 50;
	doorTile.b = 0;
	doorTile.description = "A door.";
	doorTile.blocksSight = true;
	doorTile.isSolid = false;

	std::vector<Tile> tileSet;
	tileSet.push_back(floorTile);		// 0
	tileSet.push_back(wallTile);		// 1
	tileSet.push_back(entranceTile);	// 2
	tileSet.push_back(exitTile);		// 3
	tileSet.push_back(doorTile);		// 4

	dungeon->SetTileset(tileSet);

	//FloodFill(0, 0, -1, 1, dungeon);

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
				dungeon->SetTile(x + (*it).x, y + (*it).y, -1);
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
					if (!dungeon->GetTile(x + dx, y + dy).isSolid)
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
	
	FloodFill(rooms.front().x, rooms.front().y, -1, 0, dungeon);
	
	int loop = 0;
	bool done = false;
	while (!done && loop < 100)
	{
		done = true;
		std::vector<SDL_Point> connectors;
		for (int x = 1; x < p_iWidth - 1; x++)
		{
			for (int y = 1; y < p_iHeight - 1; y++)
			{
				if (dungeon->GetTileId(x, y) == 0)
				{
					if (dungeon->GetTileId(x - 2, y) == -1 && x > 1)
					{
						SDL_Point newConnector;
						newConnector.x = x - 1;
						newConnector.y = y;
						connectors.push_back(newConnector);
					}

					if (dungeon->GetTileId(x + 2, y) == -1 && x < p_iWidth)
					{
						SDL_Point newConnector;
						newConnector.x = x + 1;
						newConnector.y = y;
						connectors.push_back(newConnector);
					}

					if (dungeon->GetTileId(x, y - 2) == -1 && y > 1)
					{
						SDL_Point newConnector;
						newConnector.x = x;
						newConnector.y = y - 1;
						connectors.push_back(newConnector);
					}

					if (dungeon->GetTileId(x, y + 2) == -1 && y < p_iHeight)
					{
						SDL_Point newConnector;
						newConnector.x = x;
						newConnector.y = y + 1;
						connectors.push_back(newConnector);
					}
				}
				else if (dungeon->GetTileId(x, y) == -1)
				{
					done = false;
				}
			}
		}
		if (connectors.size() != 0)
		{
			int rng = rand() % connectors.size();
			SDL_Point connector = connectors.at(rng);
			dungeon->SetTile(connector, 4);
			FloodFill(connector.x, connector.y, -1, 0, dungeon);

			if (rand() % 100 < 25)
			{
				connectors.erase(connectors.begin() + rng);

				rng = rand() % connectors.size();
				SDL_Point connector = connectors.at(rng);
				dungeon->SetTile(connectors.at(rng), 4);
				FloodFill(connector.x, connector.y, -1, 0, dungeon);
			}
		}
		loop++;
	}
	loop = 0;
	done = false;
	while (!done && loop < 100)
	{
		done = true;
		for (int x = 1; x < p_iWidth - 1; x++)
		{
			for (int y = 1; y < p_iHeight - 1; y++)
			{
				if (dungeon->GetTile(x, y).isSolid == false)
				{
					int count = 0;
					if (!dungeon->GetTile(x - 1, y).isSolid)
					{
						count++;
					}
					if (!dungeon->GetTile(x + 1, y).isSolid)
					{
						count++;
					}
					if (!dungeon->GetTile(x, y - 1).isSolid)
					{
						count++;
					}
					if (!dungeon->GetTile(x, y + 1).isSolid)
					{
						count++;
					}

					if (count < 2)
					{
						dungeon->SetTile(x, y, 1);
						done = false;
					}
				}
			}
		}
		loop++;
	}

	int entranceRoom;
	int exitRoom;
	do
	{
		entranceRoom = rand() % rooms.size();
		exitRoom = rand() % rooms.size();
	} while (entranceRoom == exitRoom);
	
	SDL_Point entrancePos;
	SDL_Point exitPos;

	entrancePos.x = rooms.at(entranceRoom).x + rand() % (rooms.at(entranceRoom).w - 1);
	entrancePos.y = rooms.at(entranceRoom).y + rand() % (rooms.at(entranceRoom).h - 1);

	dungeon->SetEntrance(entrancePos);
	dungeon->SetTile(entrancePos, 2);

	exitPos.x = rooms.at(exitRoom).x + rand() % (rooms.at(exitRoom).w - 1);
	exitPos.y = rooms.at(exitRoom).y + rand() % (rooms.at(exitRoom).h - 1);

	dungeon->SetExit(exitPos);
	dungeon->SetTile(exitPos, 3);

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

// Fills an empty area with a maze. "Maze bucket-fill"
void DungeonGenerator::MazeGen(int p_iX, int p_iY, TileMap* p_pxMap)
{
	p_pxMap->SetTile(p_iX, p_iY, -1);

	std::vector<int> dirs; // Available directions from this position, stored in "numpad-format". Look at your numpad and then the number and you'll get it.
	if (p_pxMap->GetTile(p_iX - 1, p_iY).isSolid) // Left
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (!p_pxMap->GetTile(p_iX - 1, p_iY - 1 + i).isSolid)
			{
				enclosed = false;
			}
			if (!p_pxMap->GetTile(p_iX - 2, p_iY - 1 + i).isSolid)
			{
				enclosed = false;
			}
		}
		if (enclosed) 
		{
			dirs.push_back(4);
		}
	}
	
	if (p_pxMap->GetTile(p_iX + 1, p_iY).isSolid) // Right
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (!p_pxMap->GetTile(p_iX + 1, p_iY - 1 + i).isSolid)
			{
				enclosed = false;
			}
			if (!p_pxMap->GetTile(p_iX + 2, p_iY - 1 + i).isSolid)
			{
				enclosed = false;
			}
		}
		if (enclosed)
		{
			dirs.push_back(6);
		}
	}

	if (p_pxMap->GetTile(p_iX, p_iY - 1).isSolid) // Up
	{
		bool enclosed = true;
		for (int i = -1; i <= 1 && enclosed; i++)
		{
			if (!p_pxMap->GetTile(p_iX + i, p_iY - 1).isSolid)
			{
				enclosed = false;
			}
			if (!p_pxMap->GetTile(p_iX + i, p_iY - 2).isSolid)
			{
				enclosed = false;
			}
		}
		if (enclosed)
		{
			dirs.push_back(8);
		}
	}

	if (p_pxMap->GetTile(p_iX, p_iY + 1).isSolid) // Down
	{
		bool enclosed = true;
		for (int i = 0; i < 3 && enclosed; i++)
		{
			if (!p_pxMap->GetTile(p_iX - 1 + i, p_iY + 1).isSolid)
			{
				enclosed = false;
			}
			if (!p_pxMap->GetTile(p_iX - 1 + i, p_iY + 2).isSolid)
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

void DungeonGenerator::FloodFill(int p_iX, int p_iY, int p_iTargetTile, int p_iReplacementTile, TileMap * p_pxMap)
{	
	if (p_iX < 0 ||
		p_iY < 0 ||
		p_iX >= p_pxMap->GetWidth() ||
		p_iY >= p_pxMap->GetHeight())
	{
		return;
	}
	if (p_pxMap->GetTileId(p_iX, p_iY) == p_iTargetTile)
	{
		p_pxMap->SetTile(p_iX, p_iY, p_iReplacementTile);
	}
	if (p_pxMap->GetTileId(p_iX - 1, p_iY) == p_iTargetTile)
	{
		FloodFill(p_iX - 1, p_iY, p_iTargetTile, p_iReplacementTile, p_pxMap);
	}
	if (p_pxMap->GetTileId(p_iX + 1, p_iY) == p_iTargetTile)
	{
		FloodFill(p_iX + 1, p_iY, p_iTargetTile, p_iReplacementTile, p_pxMap);
	}
	if (p_pxMap->GetTileId(p_iX, p_iY - 1) == p_iTargetTile)
	{
		FloodFill(p_iX, p_iY - 1, p_iTargetTile, p_iReplacementTile, p_pxMap);
	}
	if (p_pxMap->GetTileId(p_iX, p_iY + 1) == p_iTargetTile)
	{
		FloodFill(p_iX, p_iY + 1, p_iTargetTile, p_iReplacementTile, p_pxMap);
	}
	
}
