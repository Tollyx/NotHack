#pragma once

struct Tile;

enum EENTITYTYPE
{
	ENTITY_CREATURE,
	ENTITY_ITEM
};

class Sprite;
class Collider;

class IEntity
{
public:
	~IEntity() {};
	virtual void Update() = 0;
	virtual Tile GetTile() = 0;
	virtual int GetX() = 0;
	virtual int GetY() = 0;
	virtual void SetPos(int p_iX, int p_iY) = 0;
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
};