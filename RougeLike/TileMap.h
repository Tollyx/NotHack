#pragma once
struct Tile;

class TileMap
{
public:
	TileMap(int p_iWidth, int p_iHeight);
	~TileMap();
	void SetTileset(std::vector<Tile> p_axTileset);
	Tile GetTile(SDL_Point pos);
	Tile GetTile(int p_iX, int p_iY);
	int GetTileId(SDL_Point pos);
	int GetTileId(int p_iX, int p_iY);
	void SetTile(int p_iX, int p_iY, int p_iTile);
	void SetTile(SDL_Point pos, int p_iTile);
	void SetVisible(int p_iX, int p_iY, bool p_bVisible);
	void SetSeen(int p_iX, int p_iY, bool p_bSeen);
	bool IsVisible(int p_iX, int p_iY);
	bool IsSeen(int p_iX, int p_iY);
	void clearVisible();
	void SetEntrance(SDL_Point pos);
	SDL_Point GetEntrance();
	void SetExit(SDL_Point pos);
	SDL_Point GetExit();
	int GetHeight();
	int GetWidth();
private:
	TileMap() {};
	int m_iWidth;
	int m_iHeight;
	int** m_aiTileMap;
	bool** m_aiTileMapVisible;
	bool** m_aiTileMapSeen;
	SDL_Point m_pEntrance;
	SDL_Point m_pExit;
	std::vector<Tile> m_axTileset;
};