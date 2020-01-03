#include "Physics.h"

std::vector<Physics*> Physics::PhysicsObjects;
Physics::Physics()
{
	mass = 1;
	PhysicsObjects.push_back(this);
}

Physics::~Physics()
{
}

void Physics::Addforce(Vector2 force)
{
	ApplyForces.push_back(force);
}

void Physics::Loop()
{
	if (UseGravity) //simulate gravity
	{
		ApplyForces.push_back({ 0, -mass });
	}
}

void Physics::LateLoop()
{
	for (unsigned int i = 0; i < ApplyForces.size(); i++)
	{
		Velocity.x += ApplyForces[i].x * (float)GameObject::fDeltaTime;
		Velocity.y += ApplyForces[i].y * (float)GameObject::fDeltaTime;
	}
	ApplyForces.clear();
	parent->Position.x += Velocity.x * (float)GameObject::fDeltaTime;
	parent->Position.y += Velocity.y * (float)GameObject::fDeltaTime;

}

std::vector<Collider*> Collider::Colliders;

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Loop()
{
	for (int i = 0; i < Colliders.size(); i++)
	{
		Colliders[i]->CheckCollision();
	}
}

void Collider::Init()
{
	bool hasPhysicsDependancy = false;
	/*for (int i = 0; i < parent->Components.size(); i++)
	{
		if (parent->Components[i] != nullptr)
		{
			Component* pTemp = parent->Components[i];
			Physics* dep = dynamic_cast<Physics*>(pTemp);
			if (dep != nullptr)
			{
				hasPhysicsDependancy = true;
				base = dep;
				break;
			}
		}
	}*/ //Code is replaced by Object::FindComponent
	Physics* pTemp = parent->FindComponent<Physics>();
	if (pTemp != nullptr)
	{
		//hooray, it can work
		base = pTemp;
	}
	else
	{
		throw std::exception("Physics not located, exception thrown");
	}

	Colliders.push_back(this);
}
bool Collider::LineLine(GeoLine gl1, GeoLine gl2, bool Obsolete)
{
	float uA = ((gl2.end.x - gl2.begin.x) * (gl1.begin.y - gl2.begin.y)) -
		((gl2.end.y - gl2.begin.y) * (gl1.begin.x - gl2.begin.x)) /
		((gl2.end.y - gl2.begin.y) * (gl1.end.x - gl1.begin.x) -
		(gl2.end.x - gl2.begin.x) * gl1.end.y - gl1.begin.y);
	//that's quite some code there. another bit coming

	float uB = ((gl1.end.y - gl1.begin.x) * (gl1.begin.y - gl2.begin.y)) -
		((gl1.end.y - gl1.begin.y) * (gl1.begin.x - gl2.begin.x)) /
		((gl2.end.y - gl2.begin.y) * (gl1.end.x - gl1.begin.x) -
		(gl2.end.x - gl2.begin.x) * gl1.end.y - gl1.begin.y);
	//your brain hurting already? see this page: 
	//http://www.jeffreythompson.org/collision-detection/line-line.php

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}
	return false;
}
bool Collider::LineLine(GeoLine line1, GeoLine line2)
{
	float denominator = (
		(line1.end.x - line1.begin.x) *
		(line2.end.y - line2.begin.y)) -
		((line1.end.y - line1.begin.y) *
		(line2.end.x - line2.begin.x)
			);
	float numerator1 = (
		(line1.begin.y - line2.begin.y) *
		(line2.end.x - line2.begin.x)) -
		((line1.begin.x - line2.begin.x) *
		(line2.end.y - line2.begin.y)
			);
	float numerator2 = (
		(line1.begin.y - line2.begin.y) *
		(line1.end.x - line1.begin.x)) -
		((line1.begin.x - line2.begin.x) *
		(line1.end.y - line1.begin.y)
			);

	if (denominator == 0)
	{
		return (numerator1 == 0.0f && numerator2 == 0.0f);
	}

	float r = numerator1 / denominator;
	float s = numerator2 / denominator;

	return ((r >= 0 && r <= 1) && (s >= 0 && s <= 1));
}