#include "stdafx.h"
#include "Player.h"

Player::Player(Tile p_Tile, int p_iX, int p_iY)
{
	m_Tile = p_Tile;
	m_iX = p_iX;
	m_iY = p_iY;
	m_iMaxHP = 10;
	m_iHP = 10;
	m_iSTR = 5;
	m_iDEF = 5;
	m_iXp = 0;
	m_iLvl = 1; 
	m_iNextLvl = 2;
}

void Player::Update()
{
	return;
}

Tile Player::GetTile()
{
	return m_Tile;
}

int Player::Hurt(int p_iEnemySTR)
{
	int dmg = p_iEnemySTR - m_iDEF; // Pretty basic for now.
	if (dmg < 1) {
		dmg = 1;
	}
	m_iHP -= dmg;
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

void Player::AddXp(int p_iXp)
{
	m_iXp += p_iXp;

	while (m_iXp >= m_iNextLvl)
	{
		m_iLvl++;
		m_iXp -= m_iNextLvl;
		m_iNextLvl *= 2; // I'm not even trying at this point
		// TODO: Stat increases.
	}
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
	return m_iNextLvl;
}

bool Player::IsVisible()
{
	return true;
}

EENTITYTYPE Player::GetType()
{
	return EENTITYTYPE::ENTITY_PLAYER;
}
