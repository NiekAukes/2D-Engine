#include "Polygon.h"

Polygon::~Polygon()
{
}

void Polygon::Render()
{
	Renderer::rWindowRender->DrawPolygon(&Points[0], Points.size(), color);
}

void Polygon::Loop()
{
}

void Polygon::Start()
{
}

void Polygon::Init()
{
}
