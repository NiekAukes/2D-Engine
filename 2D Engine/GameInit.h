#pragma once
#include "Object.h"
class GameInit
{
private:
	GameInit() {}
public:
	static void Initialization()
	{
		//do initialization here
	}
	static void BeginGame() // Called when game Begins
	{
		Initialization();
		for (int i = 0; i < GameObject::nObjAmount; i++)
		{
			if (GameObject::GameObjects[i] != nullptr)
			{
				GameObject::GameObjects[i]->Start(); //Do start of gameObjects
				GameObject::GameObjects[i]->PrivateStart(); //Do PrivateStart of Gameobjects (for components)
			}
		}
	}
	static void UpdateGame() // Called every frame
	{
		for (int i = 0; i < GameObject::nObjAmount; i++) //call loops of gameObjects
		{
			if (GameObject::GameObjects[i] != nullptr)
			{
				GameObject::GameObjects[i]->Loop();
				GameObject::GameObjects[i]->PrivateUpdate();
			}
		}
		for (int i = 0; i < GameObject::nObjAmount; i++)
		{
			if (GameObject::GameObjects[i] != nullptr) //call lateloop for later things
			{
				GameObject::GameObjects[i]->LateLoop();
			}
		}
	}
};

