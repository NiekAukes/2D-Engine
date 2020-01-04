#include "Object.h"
#include <stdexcept>

GameObject::GameObject()
{
	for (unsigned int i = 0; i < GameObject::GameObjects.size(); i++)
	{
		if (GameObjects[i] == nullptr)
		{
			GameObjects[i] = this;

			break;
		}
		if (i >= GameObject::GameObjects.size()) //if there's no space found, return error
		{
			throw std::exception("no space available for object", 1);
		}
	}
}

GameObject::~GameObject()
{
}

void GameObject::PrivateStart()
{
	for (unsigned int i = 0; i < Components.size(); i++) //induces start on components
	{
		if (Components[i] != NULL)
		{
			Components[i]->Start();
		}
	}
	for (unsigned int i = 0; i < Children.size(); i++) //induces start on children
	{
		if (Children[i] != NULL)
		{
			Children[i]->Start();
		}
	}
}

void GameObject::PrivateUpdate()
{
	for (unsigned int i = 0; i < Components.size(); i++)
	{
		if (Components[i] != nullptr)
		{
			Components[i]->Loop();
		}
	}
}
void GameObject::PrivateLateUpdate()
{
	for (unsigned int i = 0; i < Components.size(); i++)
	{
		if (Components[i] != nullptr)
		{
			Components[i]->LateLoop();
		}
	}
}


Component::Component()
{
}

Component::~Component()
{
}

std::vector<GameObject*> GameObject::GameObjects(1000);
double GameObject::fDeltaTime;