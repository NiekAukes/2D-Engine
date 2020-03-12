#include "PolygonCollision.h"

void PolygonCollider::CheckCollision()
{
	if (poly == nullptr) {
		poly = dynamic_cast<GeoPolygon*>(parent);
	}

	for (int i = 0; i < Colliders.size(); i++)
	{
		if (Colliders[i] != nullptr && Colliders[i] != this)
		{
			BoxCollider* pBox = dynamic_cast<BoxCollider*>(Colliders[i]);
			if (pBox != nullptr)
			{
				//collider is a boxCollider
				bool colliding = false;
				if (poly->renderPoints.size() > 0) 
				{
					for (int j = 0; j < poly->physicsPoints.size() - 1; j++)
					{
						for (int k = 0; k < 4; k++)
						{
							GeoLine l(poly->physicsPoints[j], poly->physicsPoints[j + 1]);
							if (LineLine(l, pBox->GL[k]))
							{
								//collision
								colliding = true;
								break;
								break;
							}
						}
					}
				}

				if (colliding)
				{
					//temporary, will be improved with Point Forces
					pBox->base->Velocity = { 0, 0 };
					base->Velocity = { 0, 0 };
					if (pBox->base->UseGravity)
					{
						pBox->base->Addforce({ 0, pBox->base->mass });
					}
					if (base->UseGravity)
					{
						base->Addforce({ 0,base->mass });
					}
				}
			}
			else {
				PolygonCollider* pPoly = dynamic_cast<PolygonCollider*>(Colliders[i]);
				if (pPoly != nullptr) {
					//collider is PolygonCollider
					bool colliding = false;
					if (poly->physicsPoints.size() > 0 && pPoly->poly->physicsPoints.size() > 0)
					{
						for (int j = 0; j < poly->physicsPoints.size() - 1; j++)
						{
							for (int k = 0; k < pPoly->poly->physicsPoints.size() - 1; k++)
							{
								GeoLine l(poly->physicsPoints[j], poly->physicsPoints[j + 1]);
								GeoLine m(pPoly->poly->physicsPoints[k], pPoly->poly->physicsPoints[k + 1]);
								if (LineLine(l, m))
								{
									//collision
									colliding = true;
									break;
									break;
								}
							}
						}
					}

					if (colliding)
					{
						//temporary, will be improved with Point Forces
						pPoly->base->Velocity = { 0, 0 };
						base->Velocity = { 0, 0 };
						if (pPoly->base->UseGravity)
						{
							pPoly->base->Addforce({ 0, pPoly->base->mass });
						}
						if (base->UseGravity)
						{
							base->Addforce({ 0,base->mass });
						}
					}
				}
			}
		}

	}
}
