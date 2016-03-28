#pragma once
#include "vector3.h"
struct mat3
{
	mat3() {}
	mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i) 
	{
		m[0][0] = a;	m[0][1] = b;	m[0][2] = c;
		m[1][0] = d;	m[1][1] = e;	m[1][2] = f;
		m[2][0] = g;	m[2][1] = h;	m[2][2] = i;
	}
	union
	{
		float   m[3][3];
		vec3	c[3];
		float	v[9];

	};

	vec3  operator[](unsigned idx) const { return c[idx]; }
	vec3 &operator[](unsigned idx) { return c[idx]; }

	static mat3 identity();
	static mat3 rotate(float b);
	static mat3 scale(const vec2 &xy);
	static mat3 translate(const vec2 &xy);
	mat3 transpose();
	mat3 inverse();
	float determinate();
	mat3 cofactor();

	mat3 &operator+=(const mat3 &b);
	mat3 &operator-=(const mat3 &b);
	mat3 &operator*=(const mat3 &b);
};

mat3 &operator+(const mat3 &a, const mat3 &b);
mat3 &operator-(const mat3 &a, const mat3 &b);
mat3 operator*(const mat3 &a, const mat3 &b);

vec3 operator*(const mat3 &a, const vec3 &b);
vec3 operator*(const vec3 &a, const mat3 &b);

//for testing
bool operator==(const mat3 &l, const mat3 &r);

/*
Matrix +,-,+=,-=;			[x]
Matrix *					[x]
Matrix *=;					[x]
Matrix * vector;			[x]
Determinate					[x]
Cofactor					[x]
Inverse						[x]
Transpose					[x]
Identity					[x]
Rotate						[x]
Scale						[x]
Translate					[x]
*/