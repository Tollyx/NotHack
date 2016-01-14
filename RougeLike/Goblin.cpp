#include "stdafx.h"
#include "TileManager.h"
#include "Goblin.h"


Goblin::Goblin(int p_iX, int p_iY, int p_iLvl)
{
	m_Tile.spriteId = 'g';
	m_Tile.r = 025;
	m_Tile.g = 200;
	m_Tile.b = 025;
	m_Tile.description = "A goblin. Very evil. Very.";
	m_Tile.isSolid = true;
	m_Tile.blocksSight = false;

	m_iX = p_iX;
	m_iY = p_iY;
	m_iMaxHP = 3;
	m_iHP = 3;
	m_iSTR = 3;
	m_iDEF = 3;
	m_iXp = 0;
	m_iLvl = 1;
	m_iNextLvl = 2;

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
	return Tile();
}

int Goblin::Hurt(int p_iEnemySTR)
{
	int dmg = p_iEnemySTR - m_iDEF; // Pretty basic for now.
	if (dmg < 1) {
		dmg = 1;
	}
	m_iHP -= dmg;
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

void Goblin::AddXp(int p_iXp)
{
	m_iXp += p_iXp;

	while (m_iXp >= m_iNextLvl)
	{
		m_iLvl++;
		m_iXp -= m_iNextLvl;
		m_iNextLvl *= 2; // I'm not even trying at this point
		m_iSTR += m_iLvl % 2;
		m_iDEF += m_iLvl % 2;
		m_iMaxHP += 1;
		m_iHP += 1;
	}
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
	return m_iNextLvl;
}

bool Goblin::IsVisible()
{
	return true;
}

ECREATURETYPE Goblin::GetCreatureType()
{
	return ECREATURETYPE::ENTITY_CREATURE_GOBLIN;
}
