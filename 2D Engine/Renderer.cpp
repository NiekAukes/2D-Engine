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
				}

				//create Directx 10 utils
				UINT creationFlags = D3D10_CREATE_DEVICE_BGRA_SUPPORT;
				
				hr = D3D10CreateDevice(nullptr, D3D10_DRIVER_TYPE_HARDWARE, 0,
					creationFlags, D3D10_SDK_VERSION, &p3dDevice);
				
				if (SUCCEEDED(hr))
				{
					DXGI_SWAP_CHAIN_DESC scd;
					scd.BufferDesc.Width = 0;													// width of the back buffer
					scd.BufferDesc.Height = 0;													// height
					scd.BufferDesc.RefreshRate.Numerator = 0;									// refresh rate: 0 -> do not care
					scd.BufferDesc.RefreshRate.Denominator = 1;
					scd.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_420_OPAQUE;							// the color palette to use								
					scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;		// unspecified scan line ordering
					scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;						// unspecified scaling
					scd.SampleDesc.Count = 1;													// disable msaa
					scd.SampleDesc.Quality = 0;
					scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;							// use back buffer as render target
					scd.BufferCount = 3;														// the number of buffers in the swap chain (including the front buffer)
					scd.OutputWindow = hWnd;													// set the main window as output target
					scd.Windowed = true;														// windowed, not fullscreen$
					scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;								// flip mode and discared buffer after presentation
					scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;							// allow mode switching


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
			if (RegistRenders[i]->type == RenderType::PolygonRender)
			{
				ID2D1GeometrySink* pSink = nullptr;
				ID2D1PathGeometry* pPathGeo = nullptr;

				HRESULT hr = S_OK;
				hr = pFactory->CreatePathGeometry(&pPathGeo);
				if (SUCCEEDED(hr))
				{
					// Write to the path geometry using the geometry sink.
					hr = pPathGeo->Open(&pSink);
					if (SUCCEEDED(hr))
					{
						pSink->BeginFigure((RegistRenders[i]->data.Polygons)->ToRenderPoint(), D2D1_FIGURE_BEGIN_FILLED);
						pSink->AddLines(
							Vector2::ToRenderPoints(RegistRenders[i]->data.Polygons, RegistRenders[i]->nAmount),
							RegistRenders[i]->nAmount);
						//Adds all lines using Vector2's
						pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
						hr = pSink->Close();
					}
					SafeRelease(&pSink);
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
	for (int i = 0; i < 2000; i++)
	{
		if (RegistRenders[i] == nullptr)
		{
			RegistRenders[i] = new DrawRegist();
			RegistRenders[i]->type = RenderType::PolygonRender;
			RegistRenders[i]->data.Polygons = polygons;
			RegistRenders[i]->color = color;
			break;
		}
	}
}

void Renderer::DrawCircle(Vector2 Center, float Radius, Color color)
{
}
