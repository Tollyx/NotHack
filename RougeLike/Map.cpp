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
			m_aiTileMap[x][y] = 178;
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

int Map::GetTile(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aiTileMap[p_iX][p_iY];
		}
	}
	return '.';
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

int Map::GetHeight()
{
	return m_iHeight;
}

int Map::GetWidth()
{
	return m_iWidth;
}
