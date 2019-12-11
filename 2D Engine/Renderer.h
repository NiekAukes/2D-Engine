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
#include "VectorUtil.h"
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
	//for future expansion, such as circles, triangles and other
};
enum RenderType
{
	BoxRender,
	PolygonRender,
	CircleRender
};
struct DrawRegist
{
	RenderType type;
	DrawInfo data;
	int nAmount;

};
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

	void SetupRender(HWND hWnd);
	void Distribute(HWND hWnd, PAINTSTRUCT ps, HDC hdc);

	void DrawBox(Vector2 min, Vector2 max, Color color);
	void DrawPolygon(Vector2* polygons, int ArrayLength, Color color);
	void DrawCircle(Vector2 Center, float Radius, Color color);
private:

};


#endif // !RENDERER_H