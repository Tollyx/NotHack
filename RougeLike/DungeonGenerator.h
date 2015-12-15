#pragma once

class Map;

class DungeonGenerator {
public:
	DungeonGenerator();
	static Map* GenerateMap(int p_iWidth, int p_iHeight, int p_iDensity, int p_iSeed);

private:
	static bool AABB(SDL_Rect left, SDL_Rect right);
	static void MazeGen(int p_iX, int p_iY, Map* p_pxMap);
};