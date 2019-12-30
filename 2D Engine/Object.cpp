#include "Object.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::PrivateStart()
{
	for (int i = 0; i < 20; i++)
	{
		Components[i]->Start();
	}
}

void GameObject::PrivateUpdate()
{
	for (int i = 0; i < 20; i++)
	{
		Components[i]->Loop();
	}
}

Component::Component()
{
}

Component::~Component()
{
}

GameObject* GameObject::GameObjects[1000];
int GameObject::nObjAmount = 1000;