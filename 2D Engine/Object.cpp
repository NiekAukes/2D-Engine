#include "Object.h"
namespace Engine
{
	Renderer Game::rRender;
	GameObject* Game::GameObjects[1000];
	int Game::nObjectAmount = 1000;

	GameObject::GameObject()
	{
		for (int i = 0; i < Game::nObjectAmount; i++)
		{
			if (Game::GameObjects[i] == nullptr)
			{
				Game::GameObjects[i] = this;
				break;
			}
		}

	}

	GameObject::~GameObject()
	{
	}

	void GameObject::PrivateUpdate()
	{
	}

	Component::Component()
	{
	}

	Component::~Component()
	{
	}


}