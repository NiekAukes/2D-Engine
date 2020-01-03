#include "Renderer.h"

int Renderer::nScreenHeight = 1080;
int Renderer::nScreenWidth = 1920;
Renderer* Renderer::rWindowRender = nullptr;
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
			RECT rect;
			GetClientRect(hWnd, &rect);
			nScreenWidth = rect.right;
			nScreenHeight = rect.bottom;

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
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White)); //clear screen to white
	D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

	for (int i = 0; i < 2000; i++)
	{
		if (RegistRenders[i] != nullptr)
		{
			if (RegistRenders[i]->type == RenderType::BoxRender)
			{
				D2D1_RECT_F rect = D2D1::RectF(
					RegistRenders[i]->data.boxdimensions->x,
					(RegistRenders[i]->data.boxdimensions + 1)->y,
					(RegistRenders[i]->data.boxdimensions + 1)->x,
					RegistRenders[i]->data.boxdimensions->y);


				
				ID2D1SolidColorBrush* brush;
 				HRESULT hr = pRenderTarget->CreateSolidColorBrush(
					D2D1::ColorF(
						FLOAT(RegistRenders[i]->color.Red / 256), 
						FLOAT(RegistRenders[i]->color.Green / 256),
						FLOAT(RegistRenders[i]->color.Blue / 256)),
					&brush);
				if (SUCCEEDED(hr))
				{
					pRenderTarget->FillRectangle(&rect, brush);
				}
				
			}
			
		}
		delete(RegistRenders[i]);
		
		RegistRenders[i] = nullptr;
		
	}
}

void Renderer::DrawBox(Vector2 min, Vector2 max, Color color)
{
	for (int i = 0; i < 2000; i++)
	{
		if (RegistRenders[i] == nullptr)
		{
			RegistRenders[i] = new DrawRegist();
			RegistRenders[i]->type = RenderType::BoxRender;
			RegistRenders[i]->data.boxdimensions = new Vector2[2];
			RegistRenders[i]->data.boxdimensions->x = min.x;
			RegistRenders[i]->data.boxdimensions->y = min.y;
			(RegistRenders[i]->data.boxdimensions + 1)->x = max.x;
			(RegistRenders[i]->data.boxdimensions + 1)->y = max.y;
			RegistRenders[i]->color = color;
			break;
		}
	}
}

void Renderer::DrawPolygon(Vector2* polygons, int ArrayLength, Color color)
{
}

void Renderer::DrawCircle(Vector2 Center, float Radius, Color color)
{
}
