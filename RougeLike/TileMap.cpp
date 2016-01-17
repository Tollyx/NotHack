#include "stdafx.h"
#include <time.h>
#include "IEntity.h"
#include "ICreature.h"
#include "Dijkstra.h"
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

	{
		auto it = m_apxEntities.begin();
		while (it != m_apxEntities.end())
		{
			delete (*it);
			(*it) = nullptr;
			it++;
		}
	}

	{
		auto it = m_apxDijkstra.begin();
		while (it != m_apxDijkstra.end())
		{
			delete it->second;
			it->second = nullptr;
			it++;
		}
	}
}

void TileMap::Update()
{
	auto it = m_apxEntities.begin();
	while (it != m_apxEntities.end())
	{
		if ((*it)->IsVisible())
		{
			(*it)->Update(this);
		}
		it++;
	}
}

void TileMap::AddEntity(IEntity * p_pxEntity)
{
	m_apxEntities.push_back(p_pxEntity);
}

void TileMap::RemoveEntity(IEntity * p_pxEntity)
{
	auto it = m_apxEntities.begin();
	while (it != m_apxEntities.end())
	{
		if ((*it) == p_pxEntity)
		{
			m_apxEntities.erase(it);
			return;
		}
		it++;
	}
}

std::vector<IEntity*> TileMap::GetEntities()
{
	return m_apxEntities;
}

IEntity * TileMap::GetEntityAt(int p_iX, int p_iY)
{
	auto it = m_apxEntities.begin();
	while (it != m_apxEntities.end())
	{
		if ((*it)->IsVisible())
		{
			if ((*it)->GetX() == p_iX && (*it)->GetY() == p_iY)
			{
				return (*it);
			}
		}
		it++;
	}
	return nullptr;
}

void TileMap::SetTileset(std::vector<Tile> p_axTileset)
{
	m_axTileset = p_axTileset;
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
	blank.isOpaque = false;
	blank.description = "Nothing.";
	blank.spriteId = ' ';

	return blank;
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

void TileMap::DoFOV(int p_iX, int p_iY, float p_iRadius)
{
	SetVisible(p_iX, p_iY, true);
	// Once for each octant
	CastLight(1, 1.0f, 0.0f, 0, -1, -1, 0, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, -1, 0, 0, -1, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, 0, 1, -1, 0, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, 1, 0, 0, -1, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, 0, -1, 1, 0, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, -1, 0, 0, 1, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, 0, 1, 1, 0, p_iX, p_iY, p_iRadius);
	CastLight(1, 1.0f, 0.0f, 1, 0, 0, 1, p_iX, p_iY, p_iRadius);
}

void TileMap::SetVisible(int p_iX, int p_iY, bool p_bVisible)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			m_aiTileMapVisible[p_iX][p_iY] = p_bVisible;
			if (p_bVisible)
			{
				m_aiTileMapSeen[p_iX][p_iY] = p_bVisible;
			}
		}
	}
}

void TileMap::SetSeen(int p_iX, int p_iY, bool p_bSeen)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			m_aiTileMapSeen[p_iX][p_iY] = p_bSeen;
		}
	}
}

bool TileMap::IsVisible(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aiTileMapVisible[p_iX][p_iY];
		}
	}
	return false;
}

bool TileMap::IsSeen(int p_iX, int p_iY)
{
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aiTileMapSeen[p_iX][p_iY];
		}
	}
	return false;
}

void TileMap::ClearVisible()
{
	for (int x = 0; x < m_iWidth; x++)
	{
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aiTileMapVisible[x][y] = false;
		}
	}
}

Dijkstra * TileMap::GetDijkstra(EENTITYTYPE p_eTargetEntity)
{
	auto it = m_apxDijkstra.find(p_eTargetEntity);
	if (it == m_apxDijkstra.end())
	{
		m_apxDijkstra.insert(std::pair<EENTITYTYPE, Dijkstra*>(p_eTargetEntity, new Dijkstra(this, p_eTargetEntity)));
		it = m_apxDijkstra.find(p_eTargetEntity);
	}
	return it->second;
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

// Recursive shadowcasting
// Ported from http://www.roguebasin.com/index.php?title=Improved_Shadowcasting_in_Java
// I think I understand how it works.
void TileMap::CastLight(int row, float start, float end, int xx, int xy, int yx, int yy, int startX, int startY, float radius)
{
	float newStart = 0.0f;
	if (start < end)
	{
		return;
	}
	bool blocked = false;
	for (int distance = row; distance <= radius && !blocked; distance++)
	{
		int deltaY = -distance;
		for (int deltaX = -distance; deltaX <= 0; deltaX++)
		{
			int currentX = startX + deltaX * xx + deltaY * xy;
			int currentY = startY + deltaX * yx + deltaY * yy;
			float leftSlope = (deltaX - 0.5f) / (deltaY + 0.5f);
			float rightSlope = (deltaX + 0.5f) / (deltaY - 0.5f);

			if (!(currentX >= 0 && currentY >= 0 && currentX < GetWidth() && currentY < GetHeight()) || start < rightSlope)
			{
				continue;
			}
			else if (end > leftSlope)
			{
				break;
			}

			if (sqrt(deltaX*deltaX + deltaY*deltaY) <= radius)
			{
				SetVisible(currentX, currentY, true);
			}

			if (blocked)
			{
				if (GetTile(currentX, currentY).isOpaque)
				{
					newStart = rightSlope;
					continue;
				}
				else 
				{
					blocked = false;
					start = newStart;
				}
			}
			else
			{
				if (GetTile(currentX, currentY).isOpaque && distance < radius)
				{
					blocked = true;
					CastLight(distance + 1, start, leftSlope, xx, xy, yx, yy, startX, startY, radius);
					newStart = rightSlope;
				}
			}
		}
	}
}
