#pragma once
#include "IEntity.h"

enum ECREATURETYPE 
{
	ENTITY_CREATURE_PLAYER,
	ENTITY_CREATURE_GOBLIN
};

class ICreature : public IEntity {
	virtual int GetHP() = 0;
	virtual int GetMaxHP() = 0;
	virtual int GetSTR() = 0;
	virtual int GetDEF() = 0;
	virtual int Hurt(int p_iEnemySTR) = 0; // Calculates the damage, subtracts it from the HP and then returns it.
	virtual void SetPos(int p_iX, int p_iY) = 0;
	virtual void AddXp(int p_iXp) = 0;
	virtual int GetLvl() = 0;
	virtual int GetXp() = 0;
	virtual int NextLvl() = 0;
	virtual ECREATURETYPE GetCreatureType() = 0;
	EENTITYTYPE GetType() { return EENTITYTYPE::ENTITY_CREATURE; };
};