#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
	for (int i = 0; i < 3; i++)
	{
		m_abButtons[i] = false;
	}
	m_iX = 0;
	m_iY = 0;
}

Mouse::~Mouse()
{
}

int Mouse::GetX() 
{
	return m_iX;
}

int Mouse::GetY() 
{ 
	return m_iY; 
}

void Mouse::SetPosition(int p_iX, int p_iY)
{
	m_iX = p_iX;
	m_iY = p_iY;
}

bool Mouse::IsButtonDown(int p_iIndex)
{
	if (p_iIndex < 0)
		return false;
	if (p_iIndex > 2)
		return false;

	return m_abButtons[p_iIndex];
}

void Mouse::SetButton(int p_iIndex, 
						bool p_bValue)
{
	if (p_iIndex < 0)
		return;
	if (p_iIndex > 2)
		return;

	m_abButtons[p_iIndex] = p_bValue;
}
