#pragma once
#include "Object.h"
class GeoPolygon : public GameObject
{
public:
	std::vector<Vector2> Points; 
	std::vector<Vector2> renderPoints;
	std::vector<Vector2> physicsPoints;
	Color color;
	GeoPolygon() {}
	~GeoPolygon();
	void Render();
	void Loop();
	void Start();
	void Init();
private:
	std::vector<Vector2> Edges;
};

