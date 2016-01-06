#include "stdafx.h"
#include "Player.h"

Player::Player(Tile p_Tile, int p_iX, int p_iY)
{
	m_Tile = p_Tile;
	m_iX = p_iX;
	m_iY = m_iY;
	m_iMaxHP = 10;
	m_iHP = 10;
	m_iSTR = 5;
	m_iDEF = 5;
}

void Player::Update()
{

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

bool Player::IsVisible()
{
	return true;
}

EENTITYTYPE Player::GetType()
{
	return EENTITYTYPE::ENTITY_PLAYER;
}
