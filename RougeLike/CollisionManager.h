#pragma once

class Collider;

class CollisionManager
{
public:
	static bool AABB(Collider* p_pxShapeA, Collider* p_pxShapeB);
	static bool AABB(Collider* p_pxShapeA, Collider* p_pxShapeB, 
		float& p_iOverlapX, float& p_iOverlapY);
private:

};