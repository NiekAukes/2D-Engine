#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
}

void Renderer::SetupRender(HWND hWnd)
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			if (SUCCEEDED(hr))
			{
				if (pRenderTarget != NULL)
				{
					D2D1_SIZE_F size = pRenderTarget->GetSize();
					const float x = size.width / 2;
					const float y = size.height / 2;
					const float radius = min(x, y);
					ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
				}
			}
		}
	}
}

void Renderer::Distribute(HWND hWnd, PAINTSTRUCT ps, HDC hdc)
{
}

void Renderer::DrawBox(Vector2 min, Vector2 max, Color color)
{
	for (int i = 0; i < 2000; i++)
	{
		if (RegistRenders[i]->type == Indef)
		{
			RegistRenders[i]->type = BoxRender;
			RegistRenders[i]->data.boxdimensions = new Vector2[2];
		}
	}
}

void Renderer::DrawPolygon(Vector2* polygons, int ArrayLength, Color color)
{
}

void Renderer::DrawCircle(Vector2 Center, float Radius, Color color)
{
}
