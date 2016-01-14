#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{

}

Keyboard::~Keyboard()
{

}

bool Keyboard::IsKeyDown(int p_iKeycode)
{
	auto it = m_aiPressedKeys.begin();
	while (it != m_aiPressedKeys.end())
	{
		if (p_iKeycode == (*it))
		{
			return true;
		}
		it++;
	}
}

void Keyboard::SetKey(int p_iKeycode, bool p_bValue)
{
	if (p_bValue)
	{
		auto it = m_aiPressedKeys.begin();
		while (it != m_aiPressedKeys.end())
		{
			if (p_iKeycode == (*it))
			{
				return;
			}
			it++;
		}
		m_aiPressedKeys.push_back(p_iKeycode);
	}
	else 
	{
		auto it = m_aiPressedKeys.begin();
		while (it != m_aiPressedKeys.end())
		{
			if (p_iKeycode == (*it))
			{
				m_aiPressedKeys.erase(it);
				return;
			}
			it++;
		}
	}
}
