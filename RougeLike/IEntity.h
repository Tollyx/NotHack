#pragma once

enum EENTITYTYPE
{
	ENTITY_PADDLE,
	ENTITY_BALL,
	ENTITY_BRICK
};

class Sprite;
class Collider;

class IEntity
{
public:
	~IEntity() {};
	virtual void Update(float p_fDeltaTime) = 0;
	virtual Sprite* GetSprite() = 0; // Can return null if no sprite
	virtual Collider* GetCollider() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
};