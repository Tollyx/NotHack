#pragma once

class TileMap;
enum EENTITYTYPE;

class Dijkstra
{
public:
	Dijkstra(TileMap* p_pxTileMap, EENTITYTYPE p_eEntityType);
	~Dijkstra();
	void Update();
	int GetValue(int p_iX, int p_iY);
	int GetInvertedValue(int p_iX, int p_iY);
private:
	void Clear(int** p_aaiDijkstraMap);
	void Scan(int** p_aaiDijikstraMap);
	TileMap* m_pxTileMap;
	EENTITYTYPE m_eTargetEntity;
	bool m_bNeedsUpdate;
	bool m_bInvertedNeedsUpdate;
	int m_iWidth;
	int m_iHeight;
	bool** m_aabVisited;
	int** m_aaiDijkstraMap;
	int** m_aaiInvertedDijkstraMap;
};
