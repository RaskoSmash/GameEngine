#pragma once
#include <cfloat>
#include <cmath>
//a == b
// fads(a-b) < FLT_EPSILON
// (a-FLT_EPSILON) < b && b < (a + FLT_EPSILON) {== operator} 
struct vec2
{
	vec2() :x(0), y(0) {}
	vec2(float a_x, float a_y)
		: x(a_x), y(a_y) {}
	union
	{
		struct { float x, y; };
		float v[2];
	};

	float &operator[](unsigned idx) { return v[idx]; }
	float  operator[](unsigned idx) const { return v[idx]; }

	float mag() const;
	vec2 uniNegate();
	vec2 normal();
	void normalise();
	vec2 reflect(vec2 &a);
	vec2 perp() const;
	float angle();
	static vec2 fromAngle(float a);
	vec2 operator-();

	vec2 &operator+=(vec2 &r);
	vec2 &operator-=(vec2 &r);
	vec2 &operator*=(float scal);
	vec2 &operator/=(float scal);
};

float dot(const vec2 &l, const vec2 &r);

vec2 operator+(vec2 &l, vec2 &r);
vec2 operator-(vec2 &l, vec2 &r);
vec2 operator*(float scal, vec2 &r);
vec2 operator*(vec2 &l, float scal);
vec2 operator*(vec2 &l, vec2 &r);
vec2 operator/(vec2 &l, float scal);

vec2 operator+(const vec2 &l, const vec2 &r);
vec2 operator-(const vec2 &l, const vec2 &r);
vec2 operator*(const float scal, const vec2 &r);
vec2 operator*(const vec2 &l, const float scal);
vec2 operator/(const vec2 &l, const float scal);

bool operator==(const vec2 &l, const vec2 &r);
bool operator!=(const vec2 &l, const vec2 &r);
bool operator<(const vec2 &l, const vec2 &r);
bool operator<=(const vec2 &l, const vec2 &r);
bool operator>(const vec2 &l, const vec2 &r);
bool operator>=(const vec2 &l, const vec2 &r);

vec2 interp(vec2 a, vec2 b, float a_t);
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
2D Perpendicular			[x]
2D Angle					[x]
*/