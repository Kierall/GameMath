#include "Collision.h"
#include <cmath>

#include <iostream>

Collision intersect_1D(float aMin, float aMax, float bMin, float bMax)
{
	Collision ret;
	float lPD = bMax - aMin;
	float rPD = aMax - bMin;

	ret.penetrationDepth = min(lPD, rPD);
	ret.handedness = copysign(1, rPD - lPD);

	return ret;
}

Collision intersect_AABB(const AABB & a, const AABB & b)
{
	Collision xres = intersect_1D(a.min().x, a.max().x, b.min().x, b.max().x);
	Collision yres = intersect_1D(a.min().y, a.max().y, b.min().y, b.max().y);

	xres.axis = vec2{ 1,0 };
	yres.axis = vec2{ 0,1 };

	return xres.penetrationDepth < yres.penetrationDepth? xres : yres;
}

Collision intersect_circle(const circle & a, const circle & b)
{
	Collision ret;
	ret.axis = norm(b.position - a.position);
	ret.handedness = -1;
	float p1 = dot(ret.axis, a.position);
	float p2 = dot(ret.axis, b.position);

	float Amin = p1 - a.radius;
	float Amax = p1 + a.radius;

	float Bmin = p2 - b.radius;
	float Bmax = p2 + b.radius;
	ret.penetrationDepth = intersect_1D(Amin, Amax, Bmin, Bmax).penetrationDepth;

	return ret;
}

void static_resolution(vec2 & pos, vec2 & vel, const Collision & hit, float elasticity)
{
	pos += hit.axis * hit.handedness * hit.penetrationDepth;

	if (hit.axis.y == 1)
	{
		vel.y = reflect(vel, hit.axis*hit.handedness).y * elasticity;
	}
	else//
		vel = reflect(vel, hit.axis*hit.handedness) * elasticity;
}

void dynamic_resolution(vec2 & aPos, vec2 & aVel, float aMass, vec2 & bPos, vec2 bVel,float bMass, const Collision & hit, float elasticity)
{
	vec2 rVel = aVel - bVel;

	vec2 normal = hit.axis * hit.handedness;	

	float j = -(1 + elasticity) * dot(rVel, normal) / dot(normal, normal*(1 / aMass + 1 / bMass));
	//
	aVel.x += ((j / aMass) * normal).x;
	bVel.x -= ((j / bMass) * normal).x;

	aPos.x += (normal * hit.penetrationDepth * aMass / (aMass + bMass)).x;
	bPos.x -= (normal * hit.penetrationDepth * bMass / (aMass + bMass)).x;

}
