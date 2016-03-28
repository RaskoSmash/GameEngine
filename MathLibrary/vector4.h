#pragma once
#include "vector3.h"

struct vec4
{
	vec4() :x(0), y(0), z(0), w(0) {}
	vec4(float a_x, float a_y, float a_z, float a_w)
		: x(a_x), y(a_y), z(a_z), w(a_w) {}
	union 
	{
		float v[4];
		struct { float x, y, z, w; };
		struct { vec3 xyz; float w; };
		struct { float r, g, b, a; };
	};

	/*operator float*()
	{
		return (float*) this;
	}*/

	float mag() const;
	vec4 uniNegate();
	vec4 normal();
	void normalise();
	vec4 reflect(vec4 &a);
	vec4 &operator-();

	vec4 &operator+=(vec4 &r);
	vec4 &operator-=(vec4 &r);
	vec4 &operator*=(float scal);
	vec4 &operator/=(float scal);

	float dot(vec4 &r);
};

float dot(const vec4 &l, const vec4 &r);

vec4 operator+(vec4 &l, vec4 &r);
vec4 operator-(vec4 &l, vec4 &r);
vec4 operator*(float scal, vec4 &r);
vec4 operator*(vec4 &l, float scal);
vec4 operator/(vec4 &l, float scal);

bool operator==(const vec4 &l, const vec4 &r);
bool operator!=(const vec4 &l, const vec4 &r);
bool operator<(const vec4 &l, const vec4 &r);
bool operator<=(const vec4 &l, const vec4 &r);
bool operator>(const vec4 &l, const vec4 &r);
bool operator>=(const vec4 &l, const vec4 &r);

vec4 interp(vec4 a, vec4 b, float a_t);

/*
Vector +,-,+=,-=;			[x]
Vector *,*= /, /=;			[x]
==,!=, <, <=, >, >=;		[x]
Dot Product					[x]
Unary Negation				[x]
Interpolation				[x]
Reflection					[x]
Length						[x]
Normal						[x]
*/