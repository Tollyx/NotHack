#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_abKeys[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

bool Keyboard::IsKeyDown(int p_iIndex)
{
	if (p_iIndex < 0)
		return false;
	if (p_iIndex > 255)
		return false;

	return m_abKeys[p_iIndex];
}

void Keyboard::SetKey(int p_iIndex,
	bool p_bValue)
{
	if (p_iIndex < 0)
		return;
	if (p_iIndex > 255)
		return;

	m_abKeys[p_iIndex] = p_bValue;
}
