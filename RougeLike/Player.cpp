#include "stdafx.h"
#include "TileManager.h"
#include "Player.h"


Player::Player(int p_iX, int p_iY)
{
	m_Tile.spriteId = '@';
	m_Tile.r = 000;
	m_Tile.g = 127;
	m_Tile.b = 255;
	m_Tile.description = "This is you. A human. Probably.";
	m_Tile.isSolid = true;
	m_Tile.isOpaque = false;

	m_iX = p_iX;
	m_iY = p_iY;
	m_iMaxHP = 10;
	m_iHP = 10;
	m_iSTR = 5;
	m_iDEF = 5;
	m_iXp = 0;
	m_iLvl = 1; 
	m_iNextLvl = 2;
	m_bVisible = true;
}

void Player::Update(TileMap* m_pxMap, std::vector<std::string> &p_asLog)
{
	m_iHP++;
	if (m_iHP > m_iMaxHP)
	{
		m_iHP = m_iMaxHP;
	}
}

Tile Player::GetTile()
{
	return m_Tile;
}

int Player::Hurt(int p_iEnemySTR)
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

void Player::Move(int p_iX, int p_iY)
{
	m_iX += p_iX;
	m_iY += p_iY;
}

void Player::SetPos(int p_iX, int p_iY)
{
	m_iX = p_iX;
	m_iY = p_iY;
}

int Player::GetHP()
{
	return m_iHP;
}

int Player::GetMaxHP()
{
	return m_iMaxHP;
}

int Player::GetSTR()
{
	return m_iSTR;
}

int Player::GetDEF()
{
	return m_iSTR;
}

int Player::GetX()
{
	return m_iX;
}

int Player::GetY()
{
	return m_iY;
}

bool Player::AddXp(int p_iXp) // TODO: Better Lvlup thing
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

int Player::GetLvl()
{
	return m_iLvl;
}

int Player::GetXp()
{
	return m_iXp;
}

int Player::NextLvl()
{
	return m_iNextLvl - m_iXp;
}

bool Player::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Player::GetSubType()
{
	return EENTITYTYPE::ENTITY_CR_PLAYER;
}
