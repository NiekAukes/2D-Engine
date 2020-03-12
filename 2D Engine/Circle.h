#pragma once
#include "Object.h"
class GeoEllipse : public GameObject
{
public:
	float xRadius;
	float yRadius;

	Color color;
	GeoEllipse();
	~GeoEllipse();
	void Loop();
	void Render();
};

