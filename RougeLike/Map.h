#pragma once

class Map
{
public:
	Map(int p_iWidth, int p_iHeight);
	~Map();
	int GetTile(int p_iX, int p_iY);
	void SetTile(int p_iX, int p_iY, int p_iTile);
	int GetHeight();
	int GetWidth();
private:
	Map() {};
	int m_iWidth;
	int m_iHeight;
	std::vector<int> m_aiTileMap;
};