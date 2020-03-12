#pragma once
#include "Object.h"
class Box : public GameObject
{
public:
	float width = 10;
	float height = 10;
	Color color;
	Box();
	~Box();
	void Loop();
	void Render();
private:

};