#pragma once
#include "vector4.h"
struct mat4
{
	mat4() {}
	mat4(float a, float b, float c, float d, 
		float e, float f, float g, float h, 
		float i, float j, float k, float l,
		float a_m, float n, float o, float p)
	{
		m[0][0] = a;	m[0][1] = b;	m[0][2] = c;	m[0][3] = d;
		m[1][0] = e;	m[1][1] = f;	m[1][2] = g;	m[1][3] = h;
		m[2][0] = i;	m[2][1] = j;	m[2][2] = k;	m[2][3] = l;
		m[3][0] = a_m;	m[3][1] = n;	m[3][2] = o;	m[3][3] = p;
	}

	union
	{
		vec4 c[4];
		float v[16];
		float m[4][4];

		struct 
		{
			union { vec4 c1; vec4 right; };
			union { vec4 c2; vec4 up; };
			union { vec4 c3; vec4 forward; };
			union { vec4 c4; vec4 position; };
		};
	};

	static mat4 identity();
	mat4 rotate(const vec3 &a, float angle);
	mat4 scale(const vec3 &xyz);
	mat4 translate(const vec3 &xy);
	mat4 transpose();
	mat4 inverse();
	float determinate();
	mat4 cofactor();

	mat4 &operator+=(const mat4 &b);
	mat4 &operator-=(const mat4 &b);
	mat4 &operator*=(const mat4 &b);
};

mat4 &operator+(const mat4 &a, const mat4 &b);
mat4 &operator-(const mat4 &a, const mat4 &b);
mat4 &operator*(const mat4 &a, const mat4 &b);

vec4 operator*(const mat4 &a, const vec4 &b);
vec4 operator*(const vec4 &a, const mat4 &b);

mat4 OthroProjection(float right, float left, float top, float bottom, float far, float near);

/*
Matrix +,-,+=,-=;			[x]
Matrix *,*=;				[x]
Matrix * vector;			[x]
Inverse						[x]
Determinate					[x]
Cofactor					[x]
Transpose					[x]
Orthographical Projection	[x]
Identity					[x]
Rotate						[x]
Scale						[x]
Translate					[x]
*/