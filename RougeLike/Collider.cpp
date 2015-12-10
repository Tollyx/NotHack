#include "stdafx.h"
#include "Collider.h"
#include "IEntity.h"

Collider::Collider(int p_iWidth, int p_iHeight)
{
	m_xRegion.w = p_iWidth;
	m_xRegion.h = p_iHeight;
	m_xRegion.x = 0;
	m_xRegion.y = 0;
	m_pxParent = nullptr;
}

void Collider::SetPosition(int p_iX, int p_iY)
{
	m_xRegion.x = p_iX;
	m_xRegion.y = p_iY;
}

void Collider::SetSize(int p_iWidth, int p_iHeight)
{
	if (p_iWidth < 0)
	{
		m_xRegion.w = 0;
	}
	else 
	{
		m_xRegion.w = p_iHeight;
	}

	if (p_iWidth < 0)
	{
		m_xRegion.h = 0;
	}
	else
	{
		m_xRegion.h = p_iHeight;
	}
}

int Collider::GetX()
{
	return m_xRegion.x;
}

int Collider::GetY()
{
	return m_xRegion.y;
}

int Collider::GetW()
{
	return m_xRegion.w;
}

int Collider::GetH()
{
	return m_xRegion.h;
}

void Collider::SetParent(IEntity* p_pxParent)
{
	m_pxParent = p_pxParent;
}

void Collider::Refresh()
{
	if (m_pxParent != nullptr)
	{
		m_xRegion.x = m_pxParent->GetX();
		m_xRegion.y = m_pxParent->GetY();
	}
}
