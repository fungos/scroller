#include "collisionobject.h"

CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::Update(f32 dt)
{
}

void CollisionObject::Render()
{
	pRendererDevice->DrawRect(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight(), PIXEL_COLOR(255, 0, 255, 255));
}
