#pragma once

class IState;

class StateManager
{
	friend class Engine;
public:
	StateManager();
	~StateManager();
	bool Update();
	void Draw();
private:
	void SetState(IState* p_pxState);
	IState* m_pxCurrentState;
	int m_iLastTick;
};