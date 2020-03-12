#pragma once
#include "Renderer.h"
#include <vector>
class GameObject;
class Component
{
protected:
	Component();
	~Component();
public:

	GameObject* parent = nullptr;
	virtual void Start() {}
	virtual void Loop() {}
	virtual void LateLoop() {}
	virtual void Init() {}

private:
	friend class GameObject;
};

class GameObject
{
public:
	static std::vector<GameObject*> GameObjects;
	static double fDeltaTime;
	int nMaxChildrenAmount = 20;
	GameObject();
	~GameObject();
	void PrivateStart();
	void PrivateUpdate(); 
	void PrivateLateUpdate();

	std::vector<Component*> Components;
	std::vector<GameObject*> Children;

	virtual void Start() {}
	virtual void Loop() {}
	virtual void LateLoop() {}
	virtual void Render() {}

	template <class T>
	T* AddComponent()
	{
		T* newComponent = new T();
		Component* pComp = dynamic_cast<Component*>(newComponent);
		Components.push_back(pComp);
		pComp->parent = this;
		pComp->Init();
		return newComponent;
	}

	template <class T>
	T* FindComponent() //finds component in object, returns null if not found
	{
		for (unsigned int i = 0; i < Components.size(); i++)
		{
			if (Components[i] != NULL)
			{
				T* cast = dynamic_cast<T*>(Components[i]);
				if (cast != nullptr)
				{
					return cast;
				}
			}
		}
		return NULL;
	}

	Vector2 Position = {0, 0}; //position
private:
	friend class Component;
};
class Game {
public:
	static int nScreenHeight;
	static int nScreenWidth;
	static double fDeltaTime;
};