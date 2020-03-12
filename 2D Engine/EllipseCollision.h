#pragma once
#include "Physics.h"
#include "Circle.h"
#include "BoxCollision.h"
#include "PolygonCollision.h"
class EllipseCollider : public Collider
{
	GeoEllipse* ellipse;
	void CheckCollision();
};

