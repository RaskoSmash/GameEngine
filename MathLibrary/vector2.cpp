#include "vector2.h"
#pragma region dot product/ non const + - * /
float dot(const vec2 &l, const vec2 &r)
{
	return (l.x * r.x) + (l.y * r.y);
}

vec2 operator+(vec2 &l, vec2 &r)
{
	return vec2(l.x + r.x, l.y + r.y);
}

vec2 operator-(vec2 & l, vec2 &r)
{
	return vec2(l.x - r.x, l.y - r.y);
}

vec2 operator*(float scal, vec2 &r)
{
	return vec2(r.x * scal, r.y * scal);
}

vec2 operator*(vec2 &l, float scal)
{
	return vec2(l.x * scal, l.y * scal);
}

vec2 operator*(vec2 &l, vec2 &r)
{
	return vec2(r.x * l.x, r.y * l.y);
}

vec2 operator/(vec2 &l, float scal)
{
	return vec2( l.x / scal, l.y / scal );
}
#pragma endregion

#pragma region const + - * /
vec2 operator+(const vec2 &l, const vec2 &r)
{
	return vec2(l.x + r.x, l.y + r.y);
}
vec2 operator-(const vec2 &l, const vec2 &r)
{
	return vec2(l.x - r.x, l.y - r.y);
}
//vec2 operator*(const vec2 &l, const vec2 &r)
//{
//	return vec2(r.x * l.x, r.y * l.y);
//}
vec2 operator*(const float scal, const vec2 &r)
{
	return vec2(r.x * scal, r.y * scal);
}
vec2 operator*(const vec2 &l, const float scal)
{
	return vec2(l.x * scal, l.y * scal);
}
vec2 operator/(const vec2 &l, const float scal)
{
	return vec2(l.x / scal, l.y / scal);
}
#pragma endregion

#pragma region mag/uniNegate/normal/normalise/reflect/perp/angle/uniary-/ += / -= / *= / /= 
float vec2::mag() const
{
	return sqrt((x*x) + (y*y));
}

vec2 vec2::uniNegate()
{
	vec2 v;
	v.x = -x;
	v.y = -y;
	return v;
}

vec2 vec2::normal()
{
	return *this / mag();
}

void vec2::normalise()
{
	*this /= mag();
}

vec2 vec2::reflect(vec2 &a)
{
	return *this = *this - (2 * a.normal() * dot(this->normal(), a.normal()));
}

vec2 vec2::perp() const
{
	return vec2(-y, x);
}

float vec2::angle()
{
	return atan2f(y, x);
}

vec2 vec2::fromAngle(float a)
{
	return{ cosf(a), sinf(a) };
}

vec2 vec2::operator-()
{
	return vec2(-x,-y);
}

vec2 & vec2::operator+=(vec2 &r)
{
	return *this = vec2(x += r.x, y += r.y);
}

vec2 & vec2::operator-=(vec2 &r)
{
	return *this = vec2(x -= r.x, y -= r.y);
}

vec2 & vec2::operator*=(float scal)
{	
	return *this = vec2(x *= scal, y *= scal );
}

vec2 & vec2::operator/=(float scal)
{
	return *this = vec2(x /= scal, y /= scal);
}
#pragma endregion

vec2 interp(vec2 a, vec2 b, float a_t)
{
	return a_t * b + (1 - a_t) * a;
}

bool operator==(const vec2 &l, const vec2 &r)
{
	/*return r.x - FLT_EPSILON < l.x && l.x < r.x + FLT_EPSILON &&
		   r.y - FLT_EPSILON < l.y && l.y < r.y + FLT_EPSILON;*/
	return fabsf(r.x - l.x) < FLT_EPSILON && fabsf(r.y - l.y) < FLT_EPSILON;
}

bool operator!=(const vec2 &l, const vec2 &r)
{
	return !(l == r);
}

bool operator<(const vec2 &l, const vec2 &r)
{
	return l.x < r.x && l.y < r.y && l != r;
}

bool operator<=(const vec2 &l, const vec2 &r)
{
	return l < r || l == r;
}

bool operator>(const vec2 &l, const vec2 &r)
{
	return l.x > r.x && l.y > r.y && l != r;
}

bool operator>=(const vec2 &l, const vec2 &r)
{
	return l > r || l == r;
}