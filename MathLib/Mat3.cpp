#include "Mat3.h"
#include <cmath>

bool operator==(const mat3 & a, mat3 & b)
{
	return a[0] == b[0] && 
		   a[1] == b[1] && 
		   a[2] == b[2];
}

mat3 operator+(const mat3 & a, const mat3 & b)
{
	mat3 retval;
	for (int i = 0; i < 9; i++)
	{
		retval.m[i] = a.m[i] + b.m[i];
	}
	return retval;
}

mat3 operator-(const mat3 & a, const mat3 & b)
{
	mat3 retval;
	for (int i = 0; i < 9; i++)
	{
		retval.m[i] = a.m[i] - b.m[i];
	}
	return retval;
}

mat3 operator*(const mat3 & a, const mat3 & b)
{
	mat3 retval;
	mat3 at = transpose(a);
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; ++x)
		{
			retval[y][x] = dot(at[x], b[y]);
		}

	}
	return retval;
}

vec3 operator*(const mat3 & a, const vec3 & b)
{
	mat3 at = transpose(a);
	vec3 dummy{ dot(at[0], b),
			     dot(at[1], b),
				 dot(at[2], b)};
	return dummy;
}

mat3 transpose(const mat3 & a)
{
	return mat3{ a[0][0], a[1][0], a[2][0],
		a[0][1], a[1][1], a[2][1],
		a[0][2], a[1][2], a[2][2] };

	/*mat3 retval;
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			retval[x][y] = a[y][x];
		}
	}
	return retval;*/
}

float determinant(const mat3 & a)
{
	return dot(a[0], cross(a[1], a[2]));
}

mat3 inverse(const mat3 & a)
{
	float id = 1 / determinant(a);
	return transpose(mat3 { cross(a[1], a[2]) * id,
						    cross(a[2], a[0]) * id,
						    cross(a[0], a[1]) * id });
}

mat3 translation(const vec2 & t)
{
	mat3 re = mat3::identity();
	re[2].xy = t;
	return re;
}

mat3 scale(const vec2 & s)
{
	return mat3{ s.x, 0,0,
				 0, s.y, 0,
				 0, 0, 1 };
}

mat3 rotate(float deg)
{
	float rad = deg * 0.0174533;
	return{ cos(rad), sin(rad), 0,
			 -sin(rad), cos(rad),  0,
			 0,        0,         1 };
						
}

vec3 & mat3::operator[](size_t idx)
{
	return c[idx];
}

const vec3 & mat3::operator[](size_t idx) const
{
	return c[idx];
}

mat3 mat3::identity()
{
	return mat3{ 1,0,0,
		         0,1,0,
		         0,0,1 };
}
