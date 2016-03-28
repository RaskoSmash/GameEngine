#include "vector3.h"
#include <math.h>

float vec3::mag() const
{
	return sqrtf(x*x + y*y + z*z);
}

vec3 vec3::normal()
{
	return *this / mag();
}

void vec3::normalise()
{
	*this /= mag();
}

vec3 vec3::reflect(vec3 &a)
{
	return *this = *this - (2 * a.normal() * dot(a.normal()));
}

float vec3::angle()
{
	return atan2f(y, x);
}

float vec3::dot(vec3 & r)
{
	return {x * r.x + y * r.y + z * r.z};
}

float dot(vec3 &l, vec3 &r)
{
	return { l.x * r.x + l.y * r.y + l.z * r.z };
}

vec3 operator+(vec3 & l, vec3 & r)
{
	return vec3{ l.x + r.x, l.y + r.y, l.z + r.z };
}

vec3 operator-(vec3 & l, vec3 & r)
{
	return vec3{ l.x - r.x, l.y - r.y, l.z - r.z };
}

vec3 operator/(vec3 &l, float scal)
{
	return vec3(l.x / scal, l.y / scal, l.z / scal);
}

vec3 operator*(vec3 &l, float scal)
{
	return vec3(l.x * scal, l.y * scal, l.z * scal);
}

vec3 operator*(float scal, vec3 &r)
{
	return vec3(r.x * scal, r.y * scal, r.z * scal);
}

vec3 & vec3::operator-()
{
	return vec3(-x, -y, -z);
}

vec3 vec3::cross(vec3 &r)
{
	return vec3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
}

vec3 vec3::uniNegate()
{
	return -*this;
}

vec3 & vec3::operator+=(const vec3 &r)
{
	return *this = vec3(x += r.x, y += r.y, z += r.z);
}

vec3 & vec3::operator-=(const vec3 &r)
{
	return *this = vec3(x -= r.x, y -= r.y, z -= r.z);
}

vec3 & vec3::operator*=(float scal)
{
	return *this = vec3(x *= scal, y *= scal, z *= scal);
}

vec3 & vec3::operator/=(float scal)
{
	return *this = vec3(x /= scal, y /= scal, z /= scal);
}

vec3 interp(vec3 a, vec3 b, float a_t)
{
	return a_t * b + (1 - a_t) * a;
}

vec3 cross(vec3 &l, vec3 &r)
{
	return vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
}

bool operator==(const vec3 &l, const vec3 &r)
{
	return fabsf(r.x - l.x) < FLT_EPSILON && fabsf(r.y - l.y) < FLT_EPSILON && fabsf(r.z - l.z) < FLT_EPSILON;
}

bool operator!=(const vec3 &l, const vec3 &r)
{
	return !(l == r);
}

bool operator<(const vec3 &l, const vec3 &r)
{
	return l.x < r.x && l.y < r.y && l.z < r.z && l != r;
}

bool operator<=(const vec3 &l, const vec3 &r)
{
	return l < r || l == r;
}

bool operator>(const vec3 &l, const vec3 &r)
{
	return l.x > r.x && l.y > r.y && l.z > r.z && l != r;
}

bool operator>=(const vec3 &l, const vec3 &r)
{
	return l > r || l == r;
}