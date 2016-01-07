#include "stdafx.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Keyboard.h"

InputManager::InputManager(Mouse * p_pxMouse, Keyboard * p_pxKeyboard)
{
	m_pxMouse = p_pxMouse;
	m_pxKeyboard = p_pxKeyboard;
}

InputManager::~InputManager()
{
}

int InputManager::GetMouseX()
{
	return m_pxMouse->GetX();
}

int InputManager::GetMouseY()
{
	return m_pxMouse->GetY();
}

bool InputManager::IsMouseButtonDown(int p_iIndex)
{
	return m_pxMouse->IsButtonDown(p_iIndex);
}

bool InputManager::IsKeyDown(int p_iIndex)
{
	return m_pxKeyboard->IsKeyDown(p_iIndex);
}
