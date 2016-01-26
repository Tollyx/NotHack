#include "stdafx.h"
#include "TileMap.h"
#include "TileManager.h"
#include "IEntity.h"
#include "Dijkstra.h"


Dijkstra::Dijkstra(TileMap * p_pxTileMap, EENTITYTYPE p_eEntityType)
{
	m_pxTileMap = p_pxTileMap;
	m_eTargetEntity = p_eEntityType;

	m_bNeedsUpdate = true;
	m_bInvertedNeedsUpdate = true;
	m_iWidth = m_pxTileMap->GetWidth();
	m_iHeight = m_pxTileMap->GetHeight();

	m_aabVisited = new bool*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aabVisited[x] = new bool[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aabVisited[x][y] = false;
		}
	}

	m_aaiDijkstraMap = new int*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aaiDijkstraMap[x] = new int[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aaiDijkstraMap[x][y] = INT_MAX;
		}
	}

	m_aaiInvertedDijkstraMap = new int*[m_iWidth];
	for (int x = 0; x < m_iWidth; x++)
	{
		m_aaiInvertedDijkstraMap[x] = new int[m_iHeight];
		for (int y = 0; y < m_iHeight; y++)
		{
			m_aaiInvertedDijkstraMap[x][y] = INT_MAX;
		}
	}
}

Dijkstra::~Dijkstra()
{
	for (int x = 0; x < m_iWidth; x++)
	{
		delete m_aabVisited[x];
		m_aabVisited[x] = nullptr;
	}
	delete m_aabVisited;
	m_aabVisited = nullptr;

	for (int x = 0; x < m_iWidth; x++)
	{
		delete m_aaiDijkstraMap[x];
		m_aaiDijkstraMap[x] = nullptr;
	}
	delete m_aaiDijkstraMap;
	m_aaiDijkstraMap = nullptr;

	for (int x = 0; x < m_iWidth; x++)
	{
		delete m_aaiInvertedDijkstraMap[x];
		m_aaiInvertedDijkstraMap[x] = nullptr;
	}
	delete m_aaiInvertedDijkstraMap;
	m_aaiInvertedDijkstraMap = nullptr;
}


// A bunch of lies. Update() only tells it that it needs to be updated next time GetValue() is called.
void Dijkstra::Update()
{
	m_bNeedsUpdate = true;
	m_bInvertedNeedsUpdate = true;
}

int Dijkstra::GetValue(int p_iX, int p_iY)
{
	if (m_bNeedsUpdate)
	{
		Clear(m_aaiDijkstraMap);
		std::vector<IEntity*> entities = m_pxTileMap->GetEntities();
		auto it = entities.begin();
		while (it != entities.end())
		{
			if ((*it)->GetType() == m_eTargetEntity || (*it)->GetSubType() == m_eTargetEntity)
			{
				m_aaiDijkstraMap[(*it)->GetX()][(*it)->GetY()] = 0;
				m_aabVisited[(*it)->GetX()][(*it)->GetY()] = true;
			}
			it++;
		}
		Scan(m_aaiDijkstraMap);
		m_bNeedsUpdate = false;
	}
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aaiDijkstraMap[p_iX][p_iY];
		}
	}
	return INT_MAX;
}

int Dijkstra::GetInvertedValue(int p_iX, int p_iY)
{
	if (m_bInvertedNeedsUpdate)
	{
		Clear(m_aaiInvertedDijkstraMap);
		for (int x = 1; x < m_iWidth - 1; x++)
		{
			for (int y = 1; y < m_iHeight - 1; y++)
			{
				float val = GetValue(x, y);
				if (val != INT_MAX)
				{
					m_aaiInvertedDijkstraMap[x][y] = (val * -1.4f);
				}
			}
		}
		Scan(m_aaiInvertedDijkstraMap);
		m_bInvertedNeedsUpdate = false;
	}
	if (p_iX >= 0 && p_iX < m_iWidth)
	{
		if (p_iY >= 0 && p_iY < m_iHeight)
		{
			return m_aaiInvertedDijkstraMap[p_iX][p_iY];
		}
	}
	return INT_MAX;
}

void Dijkstra::Clear(int ** p_aaiDijkstraMap)
{
	for (int x = 0; x < m_iWidth; x++)
	{
		for (int y = 0; y < m_iHeight; y++)
		{
			p_aaiDijkstraMap[x][y] = INT_MAX;
			m_aabVisited[x][y] = false;
		}
	}
}

void Dijkstra::Scan(int ** p_aaiDijikstraMap)
{
	bool done = false;
	while (!done)
	{
		done = true;
		// Skip the edges of the map since they'll always be walls.
		for (int x = 1; x < m_iWidth - 1; x++)
		{
			for (int y = 1; y < m_iHeight - 1; y++)
			{
				if (!m_aabVisited[x][y])
				{
					if (m_pxTileMap->GetTile(x, y).isSolid == false && m_pxTileMap->GetEntityAt(x, y) == nullptr)
					{
						int lowest = p_aaiDijikstraMap[x][y];
						for (int dx = -1; dx <= 1; dx++)
						{
							for (int dy = -1; dy <= 1; dy++)
							{
								if ((dx != 0 || dy != 0) && p_aaiDijikstraMap[x + dx][y + dy] < lowest)
								{
									lowest = p_aaiDijikstraMap[x + dx][y + dy];
								}
							}
						}
						if (lowest < p_aaiDijikstraMap[x][y])
						{
							p_aaiDijikstraMap[x][y] = lowest + 1;
							done = false;
							m_aabVisited[x][y] = true;
						}
					}
					else
					{
						m_aabVisited[x][y] = true;
					}
				}
			}
		}
	}
}
