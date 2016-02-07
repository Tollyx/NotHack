#include "stdafx.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Keyboard.h"

InputManager::InputManager()
{
	m_pxMouse = new Mouse();
	m_pxKeyboard = new Keyboard();
}

InputManager::~InputManager()
{
	delete m_pxMouse;
	delete m_pxKeyboard;
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

bool InputManager::Update(SDL_Event p_xEvent)
{
	if (p_xEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		m_pxMouse->SetButton(p_xEvent.button.button, true);
		//return true;
	}
	else if (p_xEvent.type == SDL_MOUSEBUTTONUP)
	{
		m_pxMouse->SetButton(p_xEvent.button.button, false);
	}
	else if (p_xEvent.type == SDL_MOUSEMOTION)
	{
		m_pxMouse->SetPosition(p_xEvent.motion.x, p_xEvent.motion.y);
	}
	else if (p_xEvent.type == SDL_KEYDOWN)
	{
		//printf("Keydown: %i\n", xEvent.key.keysym.sym);
		m_pxKeyboard->SetKey(p_xEvent.key.keysym.sym, true);
		return true;
	}
	else if (p_xEvent.type == SDL_KEYUP)
	{
		//printf("Keyup: %i\n", xEvent.key.keysym.sym);
		m_pxKeyboard->SetKey(p_xEvent.key.keysym.sym, false);
		//return true;
	}
	return false;
}
