#pragma once
#include "Object.h"
class Polygon : public GameObject
{
public:
	std::vector<Vector2> Points;
	Color color;
	Polygon() {}
	~Polygon();
	void Render();
	void Loop();
	void Start();
	void Init();
private:
	std::vector<Vector2> Edges;
};

