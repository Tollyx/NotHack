#pragma once
#include "ICreature.h"

class Goblin : public ICreature {
public:
	Goblin(int p_iX, int p_iY, int p_iLvl);
	void Update(TileMap* m_pxMap, std::vector<std::string> &p_asLog);
	Tile GetTile();
	int Hurt(int p_iEnemySTR);
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
	EENTITYTYPE GetSubType();
private:
	int m_iAIState;
	int m_iX;
	int m_iY;
	Tile m_xTile;
	int m_iHP;
	int m_iMaxHP;
	int m_iSTR;
	int m_iDEF;
	int m_iXp;
	int m_iNextLvl;
	int m_iLvl;
	int m_iAICounter;
	bool m_bVisible;
};