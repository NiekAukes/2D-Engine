#ifndef RENDERER_H
#define RENDERER_H	

#pragma comment(lib, "d2d1")
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Util.h"

template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease) //saferelease
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert //define assert macro
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

struct CircleData
{
	Vector2 Center;
	float xWidth;
	float yWidth;
};
union DrawInfo
{
	Vector2* boxdimensions;
	Vector2* Polygons;
	CircleData circledata;
	DrawInfo() {}
	~DrawInfo() {}
	//for future expansion, such as circles, triangles and other
};
enum class RenderType
{
	Indef,
	BoxRender,
	PolygonRender,
	CircleRender
};
struct DrawRegist
{
	RenderType type;
	DrawInfo data;
	Color color;
	int nAmount;
	DrawRegist() {}
	~DrawRegist() {}
};
class IRenderer {

};
class Renderer : public IRenderer
{
public:
	static int nScreenHeight;
	static int nScreenWidth;
	static Renderer* rWindowRender;
	ID2D1SolidColorBrush* pBrush = NULL;
	ID2D1Factory* pFactory = NULL;
	ID2D1HwndRenderTarget* pRenderTarget = NULL;
	D2D1_ELLIPSE ellipse;

	DrawRegist* RegistRenders[2000];

	Renderer();
	~Renderer();

	void SetupRender(HWND hWnd);
	void Distribute(HWND hWnd, PAINTSTRUCT ps, HDC hdc);

	void DrawBox(Vector2 min, Vector2 max, Color color);
	void DrawPolygon(Vector2* polygons, int ArrayLength, Color color);
	void DrawCircle(Vector2 Center, float Radius, Color color);
private:

};


#endif // !RENDERER_H