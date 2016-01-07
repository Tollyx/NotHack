#pragma once

class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager(Mouse* p_pxMouse, Keyboard* p_pxKeyboard);
	~InputManager();
	//void Initialize();
	//void Shutdown();
	int GetMouseX();
	int GetMouseY();
	bool IsMouseButtonDown(int p_iIndex);
	bool IsKeyDown(int p_iIndex);
	//void Update();
private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
};
