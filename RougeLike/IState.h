#pragma once

class SpriteManager;
class DrawManager;
class InputManager;
class AudioManager;

struct System
{
	int m_iScreenWidth;
	int m_iScreenHeight;
	SpriteManager* m_pxSpriteManager;
	DrawManager* m_pxDrawManager;
	AudioManager* m_pxAudioManager;
	InputManager* m_pxInputManager;
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