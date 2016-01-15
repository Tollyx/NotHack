#include "stdafx.h"
#include "TileManager.h"
#include "Goblin.h"


Goblin::Goblin(int p_iX, int p_iY, int p_iLvl)
{
	m_xTile.spriteId = 'g';
	m_xTile.r = 025;
	m_xTile.g = 150;
	m_xTile.b = 025;
	m_xTile.description = "A goblin. Very evil. Very.";
	m_xTile.isSolid = true;
	m_xTile.blocksSight = false;

	m_iX = p_iX;
	m_iY = p_iY;
	m_iMaxHP = 3;
	m_iHP = 3;
	m_iSTR = 3;
	m_iDEF = 3;
	m_iXp = 0;
	m_iLvl = 1;
	m_iNextLvl = 2;

	m_bVisible = true;

	while (p_iLvl > m_iLvl) {
		AddXp(m_iNextLvl);
	}
}

void Goblin::Update()
{
	switch (m_iAIState)
	{
	case 1: // Idle
		break;
	case 2: // Chasing
		break;
	case 3: // Roaming
		break;
	case 4: // Fleeing
		break;
	default:
		break;
	}
}

Tile Goblin::GetTile()
{
	return m_xTile;
}

int Goblin::Hurt(int p_iEnemySTR)
{
	int dmg = p_iEnemySTR - m_iDEF; // Pretty basic for now.
	if (dmg < 1) {
		dmg = 1;
	}
	m_iHP -= dmg;
	if (m_iHP <= 0)
	{
		m_bVisible = false;
	}
	return dmg;
}

void Goblin::SetPos(int p_iX, int p_iY)
{
	m_iX = p_iX;
	m_iY = p_iY;
}

int Goblin::GetHP()
{
	return m_iHP;
}

int Goblin::GetMaxHP()
{
	return m_iMaxHP;
}

int Goblin::GetSTR()
{
	return m_iDEF;
}

int Goblin::GetDEF()
{
	return m_iDEF;
}

int Goblin::GetX()
{
	return m_iX;
}

int Goblin::GetY()
{
	return m_iY;
}

bool Goblin::AddXp(int p_iXp)
{
	m_iXp += p_iXp;
	bool lvlup = false;
	while (m_iXp >= m_iNextLvl)
	{
		m_iLvl++;
		m_iXp -= m_iNextLvl;
		m_iNextLvl *= 2; // I'm not even trying at this point
		m_iSTR += m_iLvl % 2;
		m_iDEF += m_iLvl % 2;
		m_iMaxHP += 1;
		m_iHP += 1;
		lvlup = true;
	}
	return lvlup;
}

int Goblin::GetLvl()
{
	return m_iLvl;
}

int Goblin::GetXp()
{
	return m_iXp;
}

int Goblin::NextLvl()
{
	return m_iNextLvl - m_iXp;
}

bool Goblin::IsVisible()
{
	return m_bVisible;
}

ECREATURETYPE Goblin::GetCreatureType()
{
	return ECREATURETYPE::ENTITY_CREATURE_GOBLIN;
}
