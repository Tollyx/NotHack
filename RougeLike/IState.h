#pragma once

class SpriteManager;
class DrawManager;
class Mouse;

struct System
{
	int m_iScreenWidth;
	int m_iScreenHeight;
	SpriteManager* m_pxSpriteManager;
	DrawManager* m_pxDrawManager;
	Mouse* m_pxMouse;
};

class IState
{
public:
	IState() {};
	virtual ~IState() {};
	virtual void Enter() {};
	virtual bool Update(float p_fDeltaTime) = 0;
	virtual void Exit() {};
	virtual void Draw() = 0;
	virtual IState* NextState() = 0;
};