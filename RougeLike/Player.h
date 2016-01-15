#pragma once
#include "ICreature.h"

class Player : public ICreature {
public:
	Player(int p_iX, int p_iY);
	void Update();
	Tile GetTile();
	int Hurt(int p_iEnemySTR);
	void Move(int p_iX, int p_iY);
	void SetPos(int p_iX, int p_iY);
	int GetHP();
	int GetMaxHP();
	int GetSTR();
	int GetDEF();
	int GetX();
	int GetY();
	bool AddXp(int p_iXp);
	int GetLvl();
	int GetXp();
	int NextLvl();
	bool IsVisible();
	ECREATURETYPE GetCreatureType();
private:
	int m_iX;
	int m_iY;
	Tile m_Tile;
	int m_iHP;
	int m_iMaxHP;
	int m_iSTR;
	int m_iDEF;
	int m_iXp;
	int m_iNextLvl;
	int m_iLvl;
};