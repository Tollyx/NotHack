#pragma once

class DrawManager;
class SpriteManager;
class Sprite;
class TileMap;

struct Tile {
	int spriteId;
	int r;
	int g;
	int b;
	std::string description;
	bool isSolid;
	bool blocksSight;
};

class TileManager
{
public:
	TileManager(DrawManager* p_pxDrawManager, SpriteManager* p_pxSpriteManager);
	~TileManager();
	void SetTileSet(
		std::string p_sPath,  
		int p_iTileWidth, int p_iTileHeight);

	void DrawTile(Tile p_xTile, int p_iX, int p_iY);
	void DrawTileMap(
		TileMap* p_pxTileMap, 
		int p_iX, int p_iY,
		int p_iXOffset, int p_iYOffset, 
		int p_iWidth, int p_iHeight);

	void DrawText(std::string p_sText, int p_iX, int p_iY); // TODO: Make the text colorable somehow
	int GetWindowTileWidth();
	int GetWindowTileHeight();
private:
	DrawManager* m_pxDrawManager;
	SpriteManager* m_pxSpriteManager;
	Sprite* m_apxSprites[256];
	int m_iTileWidth;
	int m_iTileHeight;
	int m_iWindowTileWidth;
	int m_iWindowTileHeight;
};
