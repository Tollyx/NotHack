#pragma once

#include "IState.h"

struct GameOverData
{
	int floor;
	int kills;
	int level;
	int turns;
	std::string killedBy;
};

class Player;

class GameOverState : public IState
{
public:
	GameOverState(System p_xSystem, GameOverData p_xData);
	~GameOverState();
	void Enter();
	bool Update(float p_fDeltaTime);
	void Exit();
	void Draw();
	IState* NextState();
private:
	System m_xSystem;
	GameOverData m_xData;
};
