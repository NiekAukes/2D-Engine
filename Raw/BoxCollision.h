#pragma once
#include "Object.h"
#include "Physics.h"
class BoxCollider : public Collider
{
public:
	
	Vector2 min;
	Vector2 max;
	BoxCollider();
	~BoxCollider();
	void Loop();
	void Start();
	void Init();

	void CheckCollision();
	void SetBoundariesFromParent(float width, float height);
	void CompileBoundaries();
	


	GeoLine GL[4];
private:
	float Width = 10;
	float Height = 10;
	friend class Physics;
	friend class Collider;
};
