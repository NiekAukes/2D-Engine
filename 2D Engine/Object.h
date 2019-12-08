#pragma once
#include "Renderer.h"
class Component
{
public:
	Component();
	~Component();

	virtual void Start() {}
	virtual void Loop() {}
	virtual void LateLoop() {}

private:

};

class GameObject
{
public:
	static GameObject* GameObjects;
	Component* Components[20];
	GameObject* Children[20];
	GameObject();
	~GameObject();
	void PrivateUpdate();

	virtual void Start() {}
	virtual void Loop() {}
	virtual void LateLoop() {}
	virtual void Render() = 0;
private:

};



