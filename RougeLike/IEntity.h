#pragma once

struct Tile;
class TileMap;

enum EENTITYTYPE
{
	ENTITY_CREATURE,
	ENTITY_CR_PLAYER,
	ENTITY_CR_MOB,

	ENTITY_ITEM,
	ENTITY_IT_EQUIPMENT,
	ENTITY_IT_CONSUMABLE
};

class Sprite;
class Collider;

class IEntity
{
public:
	~IEntity() {};
	virtual void Update(TileMap* m_pxMap) = 0;
	virtual Tile GetTile() = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual void SetPos(int p_iX, int p_iY) = 0;
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
	virtual EENTITYTYPE GetSubType() = 0;
};