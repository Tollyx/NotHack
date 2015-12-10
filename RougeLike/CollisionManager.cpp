#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include <math.h>

bool CollisionManager::Check(Collider * p_pxShapeA, Collider * p_pxShapeB, 
	int & p_iOverlapX, int & p_iOverlapY)
{
	int iACenterX = p_pxShapeA->GetX() + p_pxShapeA->GetW() / 2;
	int iBCenterX = p_pxShapeB->GetX() + p_pxShapeB->GetW() / 2;
	int iCenterDeltaX = iACenterX - iBCenterX;

	if (abs(iCenterDeltaX) < (p_pxShapeA->GetW() / 2 + p_pxShapeB->GetW() / 2)) 
	{
		int iACenterY = p_pxShapeA->GetY() + p_pxShapeA->GetH() / 2;
		int iBCenterY = p_pxShapeB->GetY() + p_pxShapeB->GetH() / 2;
		int iCenterDeltaY = iACenterY - iBCenterY;

		if (abs(iCenterDeltaY) < (p_pxShapeA->GetH() / 2 + p_pxShapeB->GetH() / 2))
		{
			int iDeltaX = (p_pxShapeA->GetW() + p_pxShapeB->GetW()) / 2 - abs(iCenterDeltaX);
			int iDeltaY = (p_pxShapeA->GetH() + p_pxShapeB->GetH()) / 2 - abs(iCenterDeltaY);

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
	}
	return false;
}
