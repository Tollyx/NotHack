#pragma once

class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager() {};
	~InputManager() {};
	void Initialize() {};
	void Shutdown() {};
	int GetMouseX() {};
	int GetMouseY() {};
	bool IsMouseButtonDown(int p_iIndex) { return false; }
	bool IsKeyDown(int p_iIndex) { return false; }
	void Update() {};
private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
};
