#include "Circle.h"

GeoEllipse::GeoEllipse()
{
}

GeoEllipse::~GeoEllipse()
{
}

void GeoEllipse::Loop()
{
}

void GeoEllipse::Render()
{
	Vector2 RenderPos = Position;
	RenderPos.y = Renderer::nScreenHeight - RenderPos.y * 10;
	RenderPos.x *= 10;
	Renderer::rWindowRender->DrawCircle(RenderPos, xRadius * 10, yRadius * 10, color);
}
