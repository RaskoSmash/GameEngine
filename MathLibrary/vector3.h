#pragma once
#include "vector2.h"
struct vec3
{
	vec3():x(0),y(0),z(0) {}
	vec3(float a_x, float a_y, float a_z)
		: x(a_x), y(a_y), z(a_z) {}
	union
	{
		struct { vec2 xy; float z; };
		struct { float x, y, z; };
		float v[3];
	};
	float mag() const;
	vec3 uniNegate();
	vec3 normal();
	void normalise();
	vec3 reflect(vec3 &a);
	float angle();
	float dot(vec3 &r);
	vec3 &operator-();
	vec3 cross(vec3 &r);

	vec3 &operator+=(const vec3 &r);
	vec3 &operator-=(const vec3 &r);
	vec3 &operator*=(float scal);
	vec3 &operator/=(float scal);
};

float dot(vec3 &l, vec3 &r);
vec3 cross(vec3 &l, vec3 &r);

vec3 operator+(vec3 &l, vec3 &r);
vec3 operator-(vec3 &l, vec3 &r);
vec3 operator*(vec3 &l, float scal);
vec3 operator*(float scal, vec3 &r);
vec3 operator/(vec3 &l, float scal);

bool operator==(const vec3 &l, const vec3 &r);
bool operator!=(const vec3 &l, const vec3 &r);
bool operator<(const vec3 &l, const vec3 &r);
bool operator<=(const vec3 &l, const vec3 &r);
bool operator>(const vec3 &l, const vec3 &r);
bool operator>=(const vec3 &l, const vec3 &r);

vec3 interp(vec3 a, vec3 b, float a_t);
/*
// Direction Between Vectors:
//(A-B).normal()
// Distance Between Vectors:
//(A-B).magnitude()
Vector +,-,+=,-=;			[x]
Vector *,*= /, /=;			[x]
==,!=, <, <=, >, >=;		[x]
Dot Product					[x]
Unary Negation				[x]
Normal						[x]
Interpolation				[x]
Reflection					[x]
Magnitude					[x]
Normal						[x]
Cross Product				[x]
*/