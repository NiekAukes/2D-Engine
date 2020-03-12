#include "BoxCollision.h"

BoxCollider::BoxCollider()
{
	
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Loop()
{
	Collider::Loop();
	SetBoundariesFromParent(Width, Height);
}

void BoxCollider::Start()
{
}

void BoxCollider::Init()
{
	Collider::Init();
	CompileBoundaries();

}

void BoxCollider::CheckCollision()
{
	for (int i = 0; i < Colliders.size(); i++)
	{
		if (Colliders[i] != nullptr && Colliders[i] != this)
		{
			BoxCollider* pBox = dynamic_cast<BoxCollider*>(Colliders[i]);
			if (pBox != nullptr)
			{
				//collider is a boxCollider
				bool colliding = false;
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (LineLine(GL[j], pBox->GL[k]))
						{
							//collision
							colliding = true;
							break;
							break;
						}
					}
				}

				if (colliding)
				{
					//temporary, will be improved with Point Forces
					pBox->base->Velocity = { 0, 0 };
					base->Velocity = { 0, 0 };
					if (pBox->base->UseGravity)
					{
						pBox->base->Addforce({ 0, pBox->base->mass });
					}
					if (base->UseGravity)
					{
						base->Addforce({ 0,base->mass });
					}
				}
			}
		}
	}
}

void BoxCollider::SetBoundariesFromParent(float width, float height)
{
	Width = width; Height = height;
	min = { parent->Position.x - width / 2, parent->Position.y - height / 2 };
	max = { parent->Position.x + width / 2, parent->Position.y + height / 2 };
	CompileBoundaries();
}

void BoxCollider::CompileBoundaries()
{

	//setting Collision lines based on Min/Max
	GL[0].begin = min;
	GL[0].end = { min.x, max.y };	//             MAX
	GL[1].begin = { min.x, max.y };	//    *---------*
	GL[1].end = max;				//    |         |
	GL[2].begin = max;				//    |         |
	GL[2].end = { max.x, min.y };	//    |         |
	GL[3].begin = { max.x, min.y };	//    *---------*
	GL[3].end = min;				//   MIN

}

