#pragma once

class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager();
	~InputManager();
	int GetMouseX();
	int GetMouseY();
	bool IsMouseButtonDown(int p_iIndex);
	bool IsKeyDown(int p_iIndex);
	bool Update(SDL_Event p_xEvent); // Returns true if the current state needs to be updated
private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
};
