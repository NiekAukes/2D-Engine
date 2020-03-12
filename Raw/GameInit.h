#pragma once
#include "Object.h"
#include "Box.h"
#include "Polygon.h"
#include "Physics.h"
#include "Circle.h"
#include "BoxCollision.h"
#include "PolygonCollision.h"
#include "EllipseCollision.h"
#include <chrono>
#include <sstream>
struct BeginV
{
	Box* b = nullptr;
	Box* ground = nullptr;
	GeoPolygon* Gp = nullptr;
	GeoPolygon* EGp = nullptr;
	GeoEllipse* Ge = nullptr;
	std::vector<Box*> particles;
};

class GameInit
{
private:
	GameInit() {}
	static std::chrono::steady_clock::time_point prevTime;
public:
	static BeginV bv;
	static bool FinishedRendering;
	static double fDeltaTime;

	static void Initialization()
	{
		//do initialization here

		bv.ground = new Box();
		bv.ground->AddComponent<Physics>();
		BoxCollider* pGCol = bv.ground->AddComponent<BoxCollider>();
		bv.ground->Position = {(float)Renderer::nScreenWidth / 20.0f, 0};
		bv.ground->width = Renderer::nScreenWidth / 20;
		pGCol->SetBoundariesFromParent(bv.ground->width, bv.ground->height);

		bv.b = new Box();
		bv.b->Position = { 60.0f, 50.0f };
		bv.b->color = { 255,0,0 };
		Physics* pPhysics = bv.b->AddComponent<Physics>();
		pPhysics->UseGravity = true;
		pPhysics->mass = 10.0f;
		BoxCollider* pBoxcol = bv.b->AddComponent<BoxCollider>();
		pBoxcol->SetBoundariesFromParent(bv.b->width, bv.b->height);

		bv.Gp = new GeoPolygon();
		Physics* pPolyPhysics = bv.Gp->AddComponent<Physics>();
		pPolyPhysics->mass = 10;
		pPolyPhysics->UseGravity = true;
		PolygonCollider* pC = bv.Gp->AddComponent<PolygonCollider>();
		bv.Gp->Position = { 100, 80.0f };
		for (long int i = 0; i < 6; i++)
		{
			Vector2 app;
			app.x = cosf(i * 60L * (3.1415f / 180)) * 2;
			app.y = sinf(i * 60L * (3.1415f / 180)) * 2;
			bv.Gp->Points.push_back(app);
		}

		bv.EGp = new GeoPolygon();
		Physics* pEPolyPhysics = bv.EGp->AddComponent<Physics>();
		pEPolyPhysics->mass = 10;
		pEPolyPhysics->UseGravity = true;
		PolygonCollider* pCE = bv.EGp->AddComponent<PolygonCollider>();
		bv.EGp->Position = { 100, 50.0f };
		for (long int i = 0; i < 6; i++)
		{
			Vector2 app;
			app.x = cosf(i * 60L * (3.1415f / 180)) * 3;
			app.y = sinf(i * 60L * (3.1415f / 180)) * 3;
			bv.EGp->Points.push_back(app);
		}

		bv.Ge = new GeoEllipse();
		Physics* pEllipsePhysics = bv.Ge->AddComponent<Physics>();
		EllipseCollider* pEllipseCollider = bv.Ge->AddComponent<EllipseCollider>();
		pEllipsePhysics->mass = 10;
		pEllipsePhysics->UseGravity = true;
		bv.Ge->Position = { 80, 50 };
		bv.Ge->color = { 255, 99,71 };
		bv.Ge->xRadius = 10;
		bv.Ge->yRadius = 10;


		/*for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 100; j++) {
				Box* b = new Box();
				b->Position.x = i;
				b->Position.y = j;
				b->height = 1;
				b->width = 1;
				bv.particles.push_back(b);
			}
		}*/


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

