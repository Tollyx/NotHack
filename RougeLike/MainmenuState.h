#pragma once
#include "IState.h"

class Sprite;

class MainmenuState : public IState
{
public:
	MainmenuState(System & p_xSystem);
	~MainmenuState();
	void Enter();
	bool Update(float p_fDeltaTime);
	void Exit();
	void Draw();
	IState* NextState();
private:
	System m_xSystem;
	std::vector<Sprite*> m_apxSprites;
	std::vector<std::string> m_asMenu;
	int m_iSelection;
};
