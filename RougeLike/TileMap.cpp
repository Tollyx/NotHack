#include "stdafx.h"
#include <time.h>
#include "TileMap.h"
#include "TileManager.h"

TileMap::TileMap(int p_iWidth, int p_iHeight)
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
	m_aiTileMapVisible = new bool*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aiTileMapVisible[x] = new bool[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aiTileMapVisible[x][y] = false;
		}
	}
	m_aiTileMapSeen = new bool*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aiTileMapSeen[x] = new bool[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aiTileMapSeen[x][y] = false;
		}
	}
}

TileMap::~TileMap()
{
	for (int x = 0; x < m_iWidth; x++)
	{
		delete m_aiTileMap[x];
	}
	delete m_aiTileMap;
}

void TileMap::SetTileset(std::vector<Tile> p_axTileset)
{
	m_axTileset = p_axTileset;
}

Tile TileMap::GetTile(SDL_Point pos)
{
	return GetTile(pos.x, pos.y);
}

Tile TileMap::GetTile(int p_iX, int p_iY)
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

int TileMap::GetTileId(SDL_Point pos)
{
	return GetTileId(pos.x, pos.y);
}

int TileMap::GetTileId(int p_iX, int p_iY)
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

void TileMap::SetTile(int p_iX, int p_iY, int p_iTile)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			m_aiTileMap[p_iX][p_iY] = p_iTile;
		}
	}
}

void TileMap::SetTile(SDL_Point pos, int p_iTile)
{
	SetTile(pos.x, pos.y, p_iTile);
}

void TileMap::SetVisible(int p_iX, int p_iY, bool p_bVisible)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			m_aiTileMapVisible[p_iX][p_iY] = p_bVisible;
		}
	}
}

void TileMap::SetSeen(int p_iX, int p_iY, bool p_bSeen)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			m_aiTileMapSeen[p_iX][p_iY] = p_bSeen;
		}
	}
}

bool TileMap::IsVisible(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			return m_aiTileMapVisible[p_iX][p_iY];
		}
	}
	return false;
}

bool TileMap::IsSeen(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth - 1)
	{
		if (p_iY >= 0 && p_iY < m_iHeight - 1)
		{
			return m_aiTileMapSeen[p_iX][p_iY];
		}
	}
	return false;
}

void TileMap::clearVisible()
{
	for (int x = 0; x < m_iWidth; x++)
	{
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aiTileMapVisible[x][y] = false;
		}
	}
}

void TileMap::SetEntrance(SDL_Point pos)
{
	m_pEntrance = pos;
}

SDL_Point TileMap::GetEntrance()
{
	return m_pEntrance;
}

void TileMap::SetExit(SDL_Point pos)
{
	m_pExit = pos;
}

SDL_Point TileMap::GetExit()
{
	return m_pExit;
}

int TileMap::GetHeight()
{
	return m_iHeight;
}

int TileMap::GetWidth()
{
	return m_iWidth;
}
