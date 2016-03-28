#include "vector4.h"

float vec4::mag() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

vec4 vec4::uniNegate()
{
	return -*this;
}

vec4 vec4::normal()
{
	return *this / mag();
}

void vec4::normalise()
{
	*this /= mag();
}


vec4 vec4::reflect(vec4 &a)
{
	return *this = *this - (2 * a.normal() * dot(a.normal()));
}

vec4 interp(vec4 a, vec4 b, float a_t)
{
	return a_t * b + (1 - a_t) * a;
}

vec4 & vec4::operator-()
{
	return vec4(-x, -y, -z, -w);
}

vec4 & vec4::operator+=(vec4 & r)
{
	return *this = vec4(x += r.x, y += r.y, z += r.z, w += r.w);
}

vec4 & vec4::operator-=(vec4 & r)
{
	return *this = vec4(x -= r.x, y -= r.y, z -= r.z, w -= r.w);
}

vec4 & vec4::operator*=(float scal)
{
	return *this = vec4(x *= scal, y *= scal, z *= scal, w *= scal);
}

vec4 & vec4::operator/=(float scal)
{
	return *this = vec4(x /= scal, y /= scal, z /= scal, w /= scal);
}

float vec4::dot(vec4 & r)
{
	return{ x * r.x + y * r.y + z * r.z + w * r.w };
}

float dot(const vec4 &l, const vec4 &r)
{
	return{ l.x * r.x + l.y * r.y + l.z * r.z + l.w + r.w };
}

vec4 operator+(vec4 &l, vec4 &r)
{
	return vec4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
}

vec4 operator-(vec4 &l, vec4 &r)
{
	return vec4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
}

vec4 operator*(float scal, vec4 &r)
{
	return vec4(r.x * scal, r.y * scal, r.z * scal, r.w * scal);
}

vec4 operator*(vec4 &l, float scal)
{
	return vec4(l.x * scal, l.y * scal, l.z * scal, l.w * scal);
}

vec4 operator/(vec4 &l, float scal)
{
	return vec4(l.x / scal, l.y / scal, l.z / scal, l.w / scal);
}

bool operator==(const vec4 &l, const vec4 &r)
{
	/*return r.x - FLT_EPSILON < l.x && l.x < r.x + FLT_EPSILON &&
	r.y - FLT_EPSILON < l.y && l.y < r.y + FLT_EPSILON &&
	r.z - FLT_EPSILON < l.z && l.z < r.z + FLT_EPSILON;*/
	return fabsf(r.x - l.x) < FLT_EPSILON && fabsf(r.y - l.y) < FLT_EPSILON && 
		   fabsf(r.z - l.z) < FLT_EPSILON && fabsf(r.w - l.w) < FLT_EPSILON;
}

bool operator!=(const vec4 &l, const vec4 &r)
{
	return !(l == r);
}

bool operator<(const vec4 &l, const vec4 &r)
{
	return l.x < r.x && l.y < r.y && l.z < r.z && l.w < r.w && l != r;
}

bool operator<=(const vec4 &l, const vec4 &r)
{
	return l < r || l == r;
}

bool operator>(const vec4 &l, const vec4 &r)
{
	return l.x > r.x && l.y > r.y && l.z > r.z && l.w > r.w && l != r;
}

bool operator>=(const vec4 &l, const vec4 &r)
{
	return l > r || l == r;
}