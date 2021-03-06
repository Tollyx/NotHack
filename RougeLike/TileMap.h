#pragma once
struct Tile;
class IEntity;
enum EENTITYTYPE;
class Dijkstra;

class TileMap
{
public:
	TileMap(int p_iWidth, int p_iHeight);
	~TileMap();

	// Entity stuff
	void Update(std::vector<std::string> &p_asLog); // Updates all entities on the map.
	void AddEntity(IEntity* p_pxEntity); // Adds an entity to the map. It will be deleted with the map unless you remove it.
	void RemoveEntity(IEntity* p_pxEntity); // NOTE: Will NOT delete the entity. Will only remove the entity from the map.
	std::vector<IEntity*> GetEntities();
	IEntity* GetEntityAt(int p_iX, int p_iY); // Does not support multiple entities on the same tile yet.

	// Tile stuff
	void SetTileset(std::vector<Tile> p_axTileset); // Should probably rename this, can get mixed up with TileManager's setTileset.
	Tile GetTile(int p_iX, int p_iY);
	int GetTileId(int p_iX, int p_iY);
	void SetTile(int p_iX, int p_iY, int p_iTile);
	void SetTile(SDL_Point pos, int p_iTile);

	// FOV Stuff, to be moved into a "Light" class
	void DoFOV(int p_iX, int p_iY, float p_iRadius);
	void SetVisible(int p_iX, int p_iY, bool p_bVisible);
	void SetSeen(int p_iX, int p_iY, bool p_bSeen);
	bool IsVisible(int p_iX, int p_iY);
	bool IsSeen(int p_iX, int p_iY);
	void ClearVisible();

	Dijkstra* GetDijkstra(EENTITYTYPE p_eTargetEntity);

	void SetEntrance(SDL_Point pos);
	SDL_Point GetEntrance();
	void SetExit(SDL_Point pos);
	SDL_Point GetExit();

	int GetHeight();
	int GetWidth();
private:
	TileMap() {};
	void CastLight(int row, float start, float end, int xx, int xy, int yx, int yy, int startX, int startY, float radius);
	int m_iWidth;
	int m_iHeight;
	int** m_aiTileMap;
	bool** m_aiTileMapVisible;
	bool** m_aiTileMapSeen; // TODO: make this an Tile array (or int, store tileId's instead?), so we can store the last known position for entities and such.
	SDL_Point m_pEntrance;
	SDL_Point m_pExit;
	std::vector<IEntity*> m_apxEntities;
	std::vector<Tile> m_axTileset;
	std::map<EENTITYTYPE, Dijkstra*> m_apxDijkstra;
};