#include "stdafx.h"
#include <time.h>
#include "Map.h"

Map::Map(int p_iWidth, int p_iHeight)
{
	m_iWidth = p_iWidth;
	m_iHeight = p_iHeight;

	m_aiTileMap = new int*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aiTileMap[x] = new int[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aiTileMap[x][y] = 1;
		}
	}
}

Map::~Map()
{
	for (int x = 0; x < m_iWidth; x++)
	{
		delete m_aiTileMap[x];
	}
	delete m_aiTileMap;
}

void Map::SetTileset(std::vector<Tile> p_axTileset)
{
	m_axTileset = p_axTileset;
}

Tile Map::GetTile(SDL_Point pos)
{
	return GetTile(pos.x, pos.y);
}

Tile Map::GetTile(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			int tileId = m_aiTileMap[p_iX][p_iY];
			if (m_axTileset.size() > tileId && tileId >= 0)
			{
				return m_axTileset.at(tileId);
			}
		}
	}

	Tile blank;
	blank.r = 0;
	blank.g = 0;
	blank.b = 0;
	blank.isSolid = false;
	blank.blocksSight = false;
	blank.description = "Nothing.";
	blank.spriteId = ' ';

	return blank;
}

int Map::GetTileId(SDL_Point pos)
{
	return GetTileId(pos.x, pos.y);
}

int Map::GetTileId(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aiTileMap[p_iX][p_iY];
		}
	}
	return -1;
}

void Map::SetTile(int p_iX, int p_iY, int p_iTile)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			m_aiTileMap[p_iX][p_iY] = p_iTile;
		}
	}
}

void Map::SetTile(SDL_Point pos, int p_iTile)
{
	SetTile(pos.x, pos.y, p_iTile);
}

void Map::SetEntrance(SDL_Point pos)
{
	m_pEntrance = pos;
}

SDL_Point Map::GetEntrance()
{
	return m_pEntrance;
}

void Map::SetExit(SDL_Point pos)
{
	m_pExit = pos;
}

SDL_Point Map::GetExit()
{
	return m_pExit;
}

int Map::GetHeight()
{
	return m_iHeight;
}

int Map::GetWidth()
{
	return m_iWidth;
}
