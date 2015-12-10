#include "stdafx.h"
#include <time.h>
#include "Map.h"

Map::Map(int p_iWidth, int p_iHeight)
{
	m_iWidth = p_iWidth;
	m_iHeight = p_iHeight;

	for (int i = 0; i < m_iWidth * m_iHeight; i++)
	{
		m_aiTileMap.push_back(std::rand() % (16 * 16));
	}
}

Map::~Map()
{
}

int Map::GetTile(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aiTileMap.at(p_iX % m_iWidth + p_iY * m_iHeight);
		}
	}
	return 0;
}

void Map::SetTile(int p_iX, int p_iY, int p_iTile)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			m_aiTileMap.assign(p_iX % m_iWidth + p_iY * m_iHeight, p_iTile);
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
