#pragma once

#include "IState.h"

class Map;
class Sprite;
class Player;
class IEntity;
class SDL_Rect;

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
	Map* m_pxMap;
	std::vector<Sprite*> m_apxSprites;
	std::vector<IEntity*> m_apxEntities;
	int m_iScreenTileWidth;
	int m_iScreenTileHeight;
	int m_iLevelDepth;
	int m_iTurns;
	Player* m_pxPlayer;
	SDL_Rect m_xCamera;
};