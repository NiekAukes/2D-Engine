#include "Box.h"

Box::Box()
{
	color.Blue = 100; color.Green = 200; color.Red = 0;
	Position = {150, 150};
}

Box::~Box()
{
}
void Box::Loop()
{
	
}

void Box::Render()
{
	if (Renderer::rWindowRender->pRenderTarget != NULL)
	{
		Renderer::rWindowRender->DrawBox(
			{(Position.x - width / 2) * 10,
			Renderer::nScreenHeight - ((Position.y - height / 2) * 10) },
			{ (Position.x + width / 2) * 10,
			Renderer::nScreenHeight - ((Position.y + height / 2) * 10) },
			{ 150, 150, 150 }); //set min & max based on pos
	}
}
