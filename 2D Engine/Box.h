#pragma once
#include "Object.h"
namespace Engine
{
	class Box : public GameObject
	{
	private:
		ID2D1SolidColorBrush* pBrush = nullptr;
		float times = 0;
	public:
		Box()
		{

		}
		void Render(HWND hWnd, HDC hdc)
		{
			
			HRESULT hr = Game::rRender.pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGreen), &pBrush);
			if (SUCCEEDED(hr))
			{
				Engine::Game::rRender.pRenderTarget->DrawLine(
					{ 100, 100 },
					{ 200, 200 },
					pBrush);
			
				D2D1_ELLIPSE ell = D2D1::Ellipse({ 300, 300 }, 100, 100);
				Engine::Game::rRender.pRenderTarget->DrawEllipse(ell, pBrush);
			}
		}
	};

}