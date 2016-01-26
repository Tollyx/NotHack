#pragma once

class TileManager;
class InputManager;
class AudioManager;

struct System
{
	TileManager* m_pxTileManager;
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