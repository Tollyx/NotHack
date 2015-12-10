#pragma once

#include "IState.h"

class Map;
class Sprite;

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
	System m_xSystem;
	Map* m_pxMap;
	std::vector<Sprite*> m_apxSprites;
	Sprite* test;
	int m_iScreenTileWidth;
	int m_iScreenTileHeight;
};