#pragma once

#include "resource.h"
#include "Object.h"
#include "Box.h"
#include <thread>

namespace Engine
{
	bool Running = true;
	void GameBegin(HWND hWnd);
	void GameUpdate(HWND hWnd);
}