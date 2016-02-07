#include "stdafx.h"
#include "TileManager.h"
#include "Goblin.h"
#include "TileMap.h"
#include "Dijkstra.h"


Goblin::Goblin(int p_iX, int p_iY, int p_iLvl)
{
	m_xTile.spriteId = 'g';
	m_xTile.r = 025;
	m_xTile.g = 150;
	m_xTile.b = 025;
	m_xTile.description = "A goblin. Very evil. Very.";
	m_xTile.isSolid = true;
	m_xTile.isOpaque = false;

	m_iX = p_iX;
	m_iY = p_iY;
	m_iMaxHP = 3;
	m_iHP = 4;
	m_iSTR = 5;
	m_iDEF = 3;
	m_iXp = 0;
	m_iLvl = 1;
	m_iNextLvl = 2;
	m_iAIState = 1;

	m_bVisible = true;

	while (p_iLvl > m_iLvl) {
		AddXp(m_iNextLvl);
	}
}

void Goblin::Update(TileMap* m_pxMap, std::vector<std::string> &p_asLog)
{
	if (m_pxMap->IsVisible(m_iX, m_iY))
	{
		m_iAICounter = 0;
	}
	else
	{
		m_iAICounter++;
		if (m_iAICounter > 5)
		{
			m_iAIState = 1;
		}
	}

	switch (m_iAIState)
	{
	case 1: // Idle
		if (m_pxMap->IsVisible(m_iX, m_iY))
		{
			if (m_iHP < m_iMaxHP / 3)
			{
				m_iAIState = 4;
			}
			else
			{
				m_iAIState = 2;
			}
		}
		break;

	case 2: // Chasing
	{
		int lowest = INT_MAX;
		int newX = 0;
		int newY = 0;
		Dijkstra* playerPath = m_pxMap->GetDijkstra(EENTITYTYPE::ENTITY_CR_PLAYER);

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				IEntity* entity = m_pxMap->GetEntityAt(m_iX + dx, m_iY + dy);
				if (entity == nullptr || entity->GetSubType() != ENTITY_CR_MOB)
				{
					int temp = playerPath->GetValue(m_iX + dx, m_iY + dy);
					if (temp < lowest)
					{
						lowest = temp;
						newX = m_iX + dx;
						newY = m_iY + dy;
					}
				}
			}
		}
		IEntity* tempEntity = m_pxMap->GetEntityAt(newX, newY);
		if (tempEntity != nullptr)
		{
			if (tempEntity->GetSubType() == EENTITYTYPE::ENTITY_CR_PLAYER)
			{
				ICreature* tempCreature = static_cast<ICreature*>(tempEntity);
				int dmg = tempCreature->Hurt(m_iSTR);
				p_asLog.push_back("Goblin hit you for " + std::to_string(dmg) + " damage.");
			}
		}
		else
		{
			m_iX = newX;
			m_iY = newY;
		}
	}
		break;

	case 3: // Roaming
		break;

	case 4: // Fleeing
	{
		int lowest = INT_MAX;
		int newX = 0;
		int newY = 0;
		Dijkstra* playerPath = m_pxMap->GetDijkstra(EENTITYTYPE::ENTITY_CR_PLAYER);

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				int temp = playerPath->GetInvertedValue(m_iX + dx, m_iY + dy);
				if (temp < lowest)
				{
					lowest = temp;
					newX = m_iX + dx;
					newY = m_iY + dy;
				}
			}
		}
		IEntity* tempEntity = m_pxMap->GetEntityAt(newX, newY);
		if (tempEntity != nullptr)
		{
			if (tempEntity->GetSubType() == EENTITYTYPE::ENTITY_CR_PLAYER)
			{
				ICreature* tempCreature = static_cast<ICreature*>(tempEntity);
				tempCreature->Hurt(m_iSTR);
			}
		}
		else
		{
			m_iX = newX;
			m_iY = newY;
			//playerPath->Update(); // Bad Idea
		}
	}
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
	int roll1 = p_iEnemySTR / 2 + rand() % p_iEnemySTR;
	int roll2 = p_iEnemySTR / 2 + rand() % p_iEnemySTR;

	int dmg;
	if (roll1 > roll2)
	{
		dmg = roll1 - m_iDEF;
	}
	else
	{
		dmg = roll2 - m_iDEF;
	}
	if (dmg < 0) {
		dmg = 0;
	}

	m_iHP -= dmg;
	if (m_iHP <= 0)
	{
		m_bVisible = false;
	}
	else if (m_iHP <= m_iMaxHP / 3)
	{
		m_iAIState = 4;
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
		m_iSTR++;
		m_iDEF++;
		m_iMaxHP += 2;
		m_iHP += 2;
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

EENTITYTYPE Goblin::GetSubType()
{
	return EENTITYTYPE::ENTITY_CR_MOB;
}
