#pragma once
#include "vector2.h"
struct mat2
{
	union
	{
		vec2 c[2];
		float m[4];
		float mm[2][2];
	};

	mat2()
	{
		c[0] = { 1,0 };
		c[1] = { 0,1 };
	}

	//used for mat3 determinate
	mat2(float a,float b,float c, float d)
	{	m[0] = a;	m[1] = b;	m[2] = c;	m[3] = d;}

	float determinate();
};

