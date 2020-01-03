#pragma once
#include "Object.h"
#include "Box.h"
#include "Physics.h"
#include "BoxCollision.h"
#include <chrono>
#include <sstream>
class GameInit
{
private:
	GameInit() {}
	static std::chrono::steady_clock::time_point prevTime;
public:
	static Box* b;
	static Box* ground;
	static bool FinishedRendering;
	static double fDeltaTime;

	static void Initialization()
	{
		//do initialization here

		ground = new Box();
		ground->AddComponent<Physics>();
		BoxCollider* pGCol = ground->AddComponent<BoxCollider>();
		ground->Position = {(float)Renderer::nScreenWidth / 20.0f, 0};
		ground->width = Renderer::nScreenWidth / 20;
		pGCol->SetBoundariesFromParent(ground->width, ground->height);

		b = new Box();
		b->Position = { 60.0f, 50.0f };
		Physics* pPhysics = b->AddComponent<Physics>();
		pPhysics->UseGravity = true;
		pPhysics->mass = 10.0f;
		BoxCollider* pBoxcol = b->AddComponent<BoxCollider>();
		pBoxcol->SetBoundariesFromParent(b->width, b->height);
	}
	static void BeginGame() // Called when game Begins
	{
		prevTime = std::chrono::high_resolution_clock::now();
		Initialization();
		for (unsigned int i = 0; i < GameObject::GameObjects.size(); i++)
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
		//calculate Deltatime

		auto newTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = newTime - prevTime;
		prevTime = newTime;
		fDeltaTime = elapsed.count();
		GameObject::fDeltaTime = fDeltaTime;

		std::wstringstream wss;
		wss << 1/fDeltaTime << '\n';
		OutputDebugString(wss.str().c_str());

		for (unsigned int i = 0; i < GameObject::GameObjects.size(); i++) //call loops of gameObjects
		{
			if (GameObject::GameObjects[i] != nullptr)
			{
				GameObject::GameObjects[i]->Loop();
				GameObject::GameObjects[i]->PrivateUpdate();
			}
		}
		for (unsigned int i = 0; i < GameObject::GameObjects.size(); i++)
		{
			if (GameObject::GameObjects[i] != nullptr) //call lateloop for later things
			{
				GameObject::GameObjects[i]->LateLoop();
				GameObject::GameObjects[i]->PrivateLateUpdate();
				GameObject::GameObjects[i]->Render();
			}
		}
	}
};

