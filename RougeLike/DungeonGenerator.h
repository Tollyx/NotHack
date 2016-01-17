#pragma once

class TileMap;

class DungeonGenerator {
public:
	DungeonGenerator();
	static TileMap* GenerateMap(int p_iWidth, int p_iHeight, int p_iDensity, int p_iLevel, int p_iSeed);

private:
	static bool AABB(SDL_Rect left, SDL_Rect right);
	static void Corridors(int p_iX, int p_iY, TileMap* p_pxMap, int p_iPreviousDir);
	static void FloodFill(int p_iX, int p_iY, int p_iTargetTile, int p_iReplacementTile, TileMap* p_pxMap);
};