#include "Polygon.h"

GeoPolygon::~GeoPolygon()
{
}

void GeoPolygon::Render()
{
	if (Points.size() > 0)
	{
		
		Renderer::rWindowRender->DrawPolygon(&renderPoints[0], renderPoints.size(), color);
	}
}

void GeoPolygon::Loop()
{
	renderPoints.clear();
	physicsPoints.clear();
	for (int i = 0; i < Points.size(); i++)
	{
		renderPoints.push_back({
			10 * (Points[i].x + Position.x),
			Renderer::nScreenHeight - 10 * (Points[i].y + Position.y)
			});
		physicsPoints.push_back({
			(Points[i].x + Position.x),
			(Points[i].y + Position.y)
			});
	}
}

void GeoPolygon::Start()
{
}

void GeoPolygon::Init()
{
}
