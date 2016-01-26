#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include <math.h>

bool CollisionManager::AABB(Collider * p_pxShapeA, Collider * p_pxShapeB)
{
	float iACenterX = p_pxShapeA->GetX() + p_pxShapeA->GetW() / 2;
	float iBCenterX = p_pxShapeB->GetX() + p_pxShapeB->GetW() / 2;
	float iCenterDeltaX = iACenterX - iBCenterX;

	if (abs(iCenterDeltaX) < (p_pxShapeA->GetW() / 2 + p_pxShapeB->GetW() / 2)) 
	{
		float iACenterY = p_pxShapeA->GetY() + p_pxShapeA->GetH() / 2;
		float iBCenterY = p_pxShapeB->GetY() + p_pxShapeB->GetH() / 2;
		float iCenterDeltaY = iACenterY - iBCenterY;

		if (abs(iCenterDeltaY) < (p_pxShapeA->GetH() / 2 + p_pxShapeB->GetH() / 2))
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::AABB(Collider * p_pxShapeA, Collider * p_pxShapeB,
	float & p_iOverlapX, float & p_iOverlapY)
{
	if (AABB(p_pxShapeA, p_pxShapeB))
	{
		float iACenterX = p_pxShapeA->GetX() + p_pxShapeA->GetW() / 2;
		float iBCenterX = p_pxShapeB->GetX() + p_pxShapeB->GetW() / 2;
		float iCenterDeltaX = iACenterX - iBCenterX;

		float iACenterY = p_pxShapeA->GetY() + p_pxShapeA->GetH() / 2;
		float iBCenterY = p_pxShapeB->GetY() + p_pxShapeB->GetH() / 2;
		float iCenterDeltaY = iACenterY - iBCenterY;

		float iDeltaX = (p_pxShapeA->GetW() + p_pxShapeB->GetW()) / 2 - abs(iCenterDeltaX);
		float iDeltaY = (p_pxShapeA->GetH() + p_pxShapeB->GetH()) / 2 - abs(iCenterDeltaY);

		if (iDeltaX < iDeltaY)
		{
			if (iDeltaX < 0) {
				p_iOverlapX = -iDeltaX;
			}
			else
			{
				p_iOverlapX = iDeltaX;
			}
		}
		else
		{
			if (iDeltaY < 0) {
				p_iOverlapY = -iDeltaY;
			}
			else
			{
				p_iOverlapY = iDeltaY;
			}
		}

		return true;
	}
	return false;
}
