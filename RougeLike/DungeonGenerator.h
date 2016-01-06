#pragma once

class Map;

class DungeonGenerator {
public:
	DungeonGenerator();
	static Map* GenerateMap(int p_iWidth, int p_iHeight, int p_iDensity, int p_iSeed);

private:
	static bool AABB(SDL_Rect left, SDL_Rect right);
	static void MazeGen(int p_iX, int p_iY, Map* p_pxMap);
	static void FloodFill(SDL_Point p_pxNode, int p_iTargetTile, int p_iReplacementTile, Map* p_pxMap);
	static const int emptyTile = 0;
	static const int floorTile = '.';
};