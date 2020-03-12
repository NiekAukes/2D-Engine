#pragma once
#include "Object.h"
class Physics : public Component
{
public:
	Physics();
	~Physics();
	Vector2 Velocity;
	bool UseGravity;
	float mass;
	void Addforce(Vector2 force);
	void Loop();
	void LateLoop();

	static std::vector<Physics*> PhysicsObjects;
protected:
	std::vector<Vector2> ApplyForces;
};

class Collider : public Component
{
public:
	Collider();
	~Collider();

	Physics* base = nullptr;
	
	virtual void Loop();
	virtual void CheckCollision() = 0;

	static std::vector<Collider*> Colliders;
	static bool LineLine(GeoLine line1, GeoLine line2);
	static bool LineLine(GeoLine gl1, GeoLine gl2, bool Obsolete);
	static bool LinePoint(GeoLine gl, Vector2 Point, float margin = 0.1f);
	static bool PointEllipse(Vector2 Point, Vector2 Radius, Vector2 EllipsePos);
	static bool LineEllipse(GeoLine gl, Vector2 Radius, Vector2 EllipsePos);

	virtual void Init();
};