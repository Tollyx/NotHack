#pragma once

class DrawManager;
class SpriteManager;
class TileManager;
class StateManager;
class Mouse;
class Keyboard;
class InputManager;
class AudioManager;

class Engine
{
public:
	Engine();
	~Engine();

	/**
	* Initializes SDL and creates all Managers
	*/
	bool Initialize(); 
	
	/**
	* Quits SDL and deletes all Managers
	*/
	void Shutdown();

	/**
	* The Engines update loop
	*/
	void Update();
	bool HandleEvents(); // returns true if the state needs to update

private:
	bool m_bRunning;
	DrawManager* m_pxDrawManager;
	SpriteManager* m_pxSpriteManager;
	TileManager* m_pxTileManager;
	AudioManager* m_pxAudioManager;
	StateManager* m_pxStateManager;
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
	InputManager* m_pxInputManager;
};
