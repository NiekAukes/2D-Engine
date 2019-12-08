#ifndef RENDERER_H
#define RENDERER_H	

#pragma comment(lib, "d2d1")
#include <d2d1.h>
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
class IRenderer {

};
class Renderer : public IRenderer
{
public:
	ID2D1SolidColorBrush* pBrush = NULL;
	ID2D1Factory* pFactory = NULL;
	ID2D1HwndRenderTarget* pRenderTarget = NULL;
	D2D1_ELLIPSE ellipse;
	Renderer();
	~Renderer();
	void RenderNow(HWND hWnd);
private:

};


#endif // !RENDERER_H