#pragma once

struct Tile {
	int tile;
	Uint32 fgColor;
	Uint32 bgColor;
	char* description;
};

class Map
{
public:
	Map(int p_iWidth, int p_iHeight);
	~Map();
	int GetTile(SDL_Point pos);
	int GetTile(int p_iX, int p_iY);
	void SetTile(int p_iX, int p_iY, int p_iTile);
	void SetTile(SDL_Point pos, int p_iTile);
	int GetHeight();
	int GetWidth();
private:
	Map() {};
	int m_iWidth;
	int m_iHeight;
	int** m_aiTileMap;
};