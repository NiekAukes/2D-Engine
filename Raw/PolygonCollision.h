#pragma once
#include "Physics.h"
#include "Polygon.h"
#include "BoxCollision.h"
class PolygonCollider : public Collider
{
private:
public:
	GeoPolygon* poly;
	void CheckCollision();
};

