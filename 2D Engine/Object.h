#pragma once
#include "Renderer.h"
#include "VectorUtil.h"
#include <Windows.h>
#include <chrono>

namespace Engine
{

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
		Component* Components[20];
		GameObject* Children[20];

		Vector2 Position;
		float Rotation = 0.0f;

		GameObject();
		~GameObject();
		void PrivateUpdate();

		virtual void Start() {}
		virtual void Loop() {}
		virtual void LateLoop() {}
		virtual void Render(HWND hWnd, HDC hdc) {};
	private:

	};

	class Game
	{
	public:
		static Renderer rRender;
		static GameObject* GameObjects[1000];
		static int nObjectAmount;
	};

	class Camera
	{
		static Vector2 Position;
		static
	};

}