#pragma once
#include "Transform.h"
class Sprite
{
public:
	int handle;
	vec2 dim;
	vec2 offset;
	Sprite(float a_handle = -1.f, float width = 1.f, float height = 1.f) : handle(a_handle), dim{ width, height }, offset{ 0,0 }
	{

	}
	void draw(const Transform &t, const mat3 &cam = mat3::identity())
	{
		mat3 m = cam * t.GetGlobalTransform() * translation(offset) * scale(dim);
		sfw::drawTextureMatrix3(handle, 0, WHITE, m.m);
	}


};
