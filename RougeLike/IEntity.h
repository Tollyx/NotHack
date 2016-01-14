#pragma once

struct Tile;

enum EENTITYTYPE
{
	ENTITY_PLAYER,
	ENTITY_MONSTER
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
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
};