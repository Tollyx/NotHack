#pragma once

#include "IState.h"

class TileMap;
class Sprite;
class Player;
class IEntity;
class SDL_Rect;
class Mix_Chunk;

class GameState : public IState
{
public:
	GameState(System& p_xSystem);
	~GameState();
	void Enter();
	bool Update(float p_fDeltaTime);
	void Exit();
	void Draw();
	IState* NextState();
private:
	void NewMap();
	System m_xSystem;
	TileMap* m_pxMap;
	int m_iLevelDepth;
	int m_iTurns;
	Player* m_pxPlayer;
	SDL_Rect m_xCamera;
};