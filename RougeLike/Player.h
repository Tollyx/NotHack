#pragma once

#include "IEntity.h"

class Player : public IEntity {
public:
	Player(Tile p_Tile, int p_iX, int p_iY);
	void Update();
	Tile GetTile();
	int Hurt(int p_iEnemySTR); // Calculates the damage, subtracts it from the HP and then returns it.
	int GetHP();
	int GetMaxHP();
	int GetSTR();
	int GetDEF();
	int GetX();
	int GetY();
	bool IsVisible();
	EENTITYTYPE GetType();
private:
	int m_iX;
	int m_iY;
	Tile m_Tile;
	int m_iHP;
	int m_iMaxHP;
	int m_iSTR;
	int m_iDEF;
};