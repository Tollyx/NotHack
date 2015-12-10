#pragma once

class Collider;

class CollisionManager
{
public:
	static bool Check(Collider* p_pxShapeA, Collider* p_pxShapeB, 
		int& p_iOverlapX, int& p_iOverlapY);
private:

};