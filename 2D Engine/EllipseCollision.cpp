#include "EllipseCollision.h"

void EllipseCollider::CheckCollision()
{
	if (ellipse == nullptr) {
		ellipse = dynamic_cast<GeoEllipse*>(parent);
	}

	for (int i = 0; i < Colliders.size(); i++)
	{
		if (Colliders[i] != nullptr && Colliders[i] != this)
		{
			bool colliding = false;
			BoxCollider* pBox = dynamic_cast<BoxCollider*>(Colliders[i]);
			if (pBox != nullptr)
			{
				//collider is a boxCollider
				for (int j = 0; j < 4; j++) {
					if (LineEllipse(pBox->GL[j], { ellipse->xRadius, ellipse->yRadius }, ellipse->Position)) {
						colliding = true;
					}
				}
			}
			else {
				PolygonCollider* pPoly = dynamic_cast<PolygonCollider*>(Colliders[i]);
				if (pPoly != nullptr)
				{
					//collider is a PolygonCollider
					if (pPoly->poly->renderPoints.size() > 0)
					{
						for (int j = 0; j < pPoly->poly->physicsPoints.size() - 1; j++) {
							if (LineEllipse(
								{ pPoly->poly->physicsPoints[j], pPoly->poly->physicsPoints[j] },
								{ ellipse->xRadius, ellipse->yRadius },
								ellipse->Position)) {
								colliding = true;
							}
						}
					}
				}
				else {
					EllipseCollider* pEllipse = dynamic_cast<EllipseCollider*>(Colliders[i]);
					if (pPoly != nullptr)
					{
						//collider is an EllipseCollider
					}
					else {
						//something went wrong!
					}
				}
			}
		}
	}
}