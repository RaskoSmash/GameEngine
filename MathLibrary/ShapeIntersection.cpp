#include "ShapeIntersection.h"
#include "vector2.h"
#include <algorithm>

#pragma region min/max/clamp/distance, AABB min/max
float point_plane_dist(const vec2 & a, const plane & b)
{
	return dot(b.n, (a - b.p));
}
float ray_plane_dist(const ray & a, const plane & b)
{
	return point_plane_dist(a.p,b) / -(dot(b.n, a.d));
}
vec2 minv(const vec2 & a, const vec2 & b)
{
	vec2 imin = { FLT_MAX, FLT_MAX };
	imin.x = minf(a.x, b.x);
	imin.y = minf(a.y, b.y);

	return vec2(imin.x, imin.y);
}

vec2 maxv(const vec2 & a, const vec2 & b)
{
	vec2 imax = { FLT_MIN, FLT_MIN };
	
	imax.x = maxf(a.x, b.x);
	imax.y = maxf(a.y, b.y);

	return vec2(imax.x, imax.y);
}

vec2 clampv(const vec2 & a, const vec2 & min, const vec2 & max)
{
	return minv(maxv(a, min), max);
}

float minf(float a, float b)
{
	return (a < b ? a : b);
}

float maxf(float a, float b)
{
	return (a > b ? a : b);
}

float clampf(float a, float min, float max)
{
	return minf(maxf(a,min), max);
}

float distance(const vec2 &l, const vec2 &r)
{
	vec2 dist = l - r;
	return dist.mag();
}

vec2 aabb::min() const
{
	return p - he;
}

vec2 aabb::max() const
{
	return p + he;
}

#pragma endregion

#pragma region bool Collision Tests 

bool iTest_aabb(const aabb & a, const aabb & b)
{
	vec2 max1, max2, min1, min2;
	min1 = a.min();
	max1 = a.max();
	min2 = b.min();
	max2 = b.max();

	return max1.x >= min2.x && max2.x >= min1.x &&
		   max1.y >= min2.y && max2.y >= min1.y;
}

bool iTest_aabb_circle(const aabb & a, const circle & b)
{
	vec2 c = clampv(b.p, a.min(), a.max());
	return (distance(b.p, c) * distance(b.p, c)) <= b.r * b.r;
}

bool iTest_aabb_plane(const aabb & a, const plane & b)
{
	/*// plane point dist
	//float ppD = dot(b.n, (a.p - b.p));
	// projected extents
	//float pjE = (a.he.x * fabsf(dot(b.n, vec2(1, 0)))) + (a.he.y * fabsf(dot(b.n, vec2(0, 1))));
	// ppD <= pjE;*/
	return dot(b.n,(a.p - b.p)) <= (a.he.x * fabsf(dot(b.n, vec2(1,0)))) + (a.he.y * fabsf(dot(b.n, vec2(0,1))));
}

bool iTest_aabb_ray(const aabb & a, const ray & b)
{
	ray ray = b;
	for (int i = 0; i < 2; ++i)
	{
		ray.d.v[i] = (ray.d.v[i] == 0) ? FLT_EPSILON : ray.d.v[i];
	}

	plane s1p1 = { vec2(a.p.x, a.min().y ), vec2(0, -1)};
	plane s1p2 = { vec2(a.p.x, a.max().y), vec2(0, 1) };
	plane s2p1 = { vec2(a.min().x, a.p.y), vec2(-1, 0)}; 
	plane s2p2 = { vec2(a.max().x, a.p.y),  vec2(1, 0) };

	float tmin = FLT_MAX;
	float tmax = -FLT_MAX;
	tmin = maxf(minf(ray_plane_dist(ray, s1p1), ray_plane_dist(ray, s1p2)), 
				minf(ray_plane_dist(ray, s2p1), ray_plane_dist(ray, s2p2)));

	tmax = minf(maxf(ray_plane_dist(ray,s1p1), ray_plane_dist(ray,s1p2)), 
				maxf(ray_plane_dist(ray,s2p1), ray_plane_dist(ray,s2p2)));

	return tmin <= tmax && 0 <= tmin && tmin <= b.l;
}

bool iTest_circle(const circle & a, const circle & b)
{
	return distance(a.p, b.p) <= (a.r + b.r);
}

bool iTest_circle_plane(const circle & a, const plane & b)
{
	return point_plane_dist(a.p, b) <= a.r;
}

bool iTest_circle_ray(const circle & a, const ray & b)
{
	vec2 c = b.p + b.d * clampf(dot((a.p- b.p), b.d), 0, b.l);
	return dot(a.p - c,a.p - c) <= (a.r * a.r);
}

bool iTest_ray_plane(const ray & a, const plane & b)
{
	if (-dot(b.n, a.d) > 0)
	{
		float re = ray_plane_dist(a, b);
		return 0 <= re && re <= a.l;
	}
	else
		return false;
}

#pragma endregion

#pragma region MTV Collision

CollisionData mtv_aabb(const aabb & a, const aabb & b)
{
	if (iTest_aabb(a, b))
	{
		vec2 pD_ = minv(a.max() - b.min(), b.max() - a.min());
		float pD = minf(pD_.x, pD_.y);
		vec2 A = { 0,0 };
		vec2 H = { 0,0 };
		if (pD_.x > pD_.y)
		{
			A = { 0,1 };
			if ((a.max().y - b.min().y) - (b.max().y - a.min().y) < 0)
				H = { 0,-1 };
			else
				H = { 0,1 };
		}
		else
		{
			A = { 1,0 };
			if ((a.max().x - b.min().x) - (b.max().x - a.min().x) < 0)
				H = { -1,0 };
			else
				H = { 1,0 };
		}
		vec2 cNor = H * A;
		return{ true, pD, {cNor}, {cNor * pD} };

	}
	else
		return{ false,0,{ 0,0 },{ 0,0 } };
}

CollisionData mtv_aabb_circle(const aabb & a, const circle & b)
{
	if (iTest_aabb_circle(a, b))
	{
		vec2 c = clampv(b.p, a.min(), a.max());
		float d = (b.p - c).mag();
		float pD = (b.r - d);
		vec2 cNorm = (b.p - c);
		cNorm.normalise();

		return{ true,pD,{cNorm},{cNorm * pD} };
	}
	else
		return{ false,0,{0,0}, {0,0} };
}

CollisionData mtv_aabb_plane(const aabb & a, const plane & b)
{
	if (iTest_aabb_plane(a, b))
	{
		vec2 nor = b.n;
		float pD = (a.he.x * fabsf(dot(b.n, vec2(1, 0)))) + (a.he.y * fabsf(dot(b.n, vec2(0, 1)))) - dot(b.n, (a.p - b.p));
		vec2 pD_ = { a.he.x * fabsf(dot(b.n, vec2(1, 0))), a.he.y * fabsf(dot(b.n, vec2(0, 1))) };
		vec2 A = { 0,0 };

		if (pD_.x > pD_.y)
		{
			A = { 1,0 };
		}
		else
			A = { 0,1 };

		vec2 cNor = A * nor;

		return{ true,pD,{cNor},{(cNor * pD)} };
	}
	else return{ false,0,{0,0},{0,0} };
}

CollisionData mtv_aabb_ray(const aabb & a, const ray & b)
{
	if (iTest_aabb_ray(a, b))
	{
		ray ray = b;

		plane s1p1 = { vec2(a.p.x, a.min().y), vec2(0, -1) };
		plane s1p2 = { vec2(a.p.x, a.max().y), vec2(0, 1) };
		plane s2p1 = { vec2(a.min().x, a.p.y), vec2(-1, 0) };
		plane s2p2 = { vec2(a.max().x, a.p.y),  vec2(1, 0) };

		float tmin = FLT_MAX;
		vec2 A = { 0,0 };

		float rayVs1p1 = ray_plane_dist(ray, s1p1); // Down
		float rayVs1p2 = ray_plane_dist(ray, s1p2); // Up
		float rayVs2p1 = ray_plane_dist(ray, s2p1); // Left
		float rayVs2p2 = ray_plane_dist(ray, s2p2); // Right

		tmin = maxf(minf(rayVs1p1, rayVs1p2), 
					minf(rayVs2p1, rayVs2p2));

		float pD = tmin - ray.l;

		if (fabsf(rayVs1p1 - tmin) < FLT_EPSILON)
		{
			A = s1p1.n;
		}
		else if (fabsf(rayVs1p2 - tmin) < FLT_EPSILON)
		{
			A = s1p2.n;
		}
		else if (fabsf(rayVs2p1 - tmin) < FLT_EPSILON)
		{
			A = s2p1.n;
		}
		else if(fabsf(rayVs2p2 - tmin) < FLT_EPSILON)
		{
			A = s2p2.n;
		}
		vec2 cNor = -ray.d;

		return{ true,pD,{-cNor},{-cNor * pD} };
	}
	else
		return{ false,0,{0,0},{0,0} };
}

CollisionData mtv_circle(const circle & a, const circle & b)
{
	if (iTest_circle(a, b))
	{
		float dist = distance(a.p, b.p);
		float radii = (a.r + b.r);
		float pD = radii - dist;
		vec2 cNor = (a.p - b.p);
		cNor.normalise();
		return{ true, pD,{cNor},{cNor * pD} };
	}
	else
		return{ false,0,{0,0},{0,0} };
}

CollisionData mtv_circle_plane(const circle & a, const plane & b)
{
	if (iTest_circle_plane(a, b))
	{
		float pD = point_plane_dist(a.p, b) - a.r;
		vec2 cNor = b.n;

		return{ true,pD,{-cNor},{-cNor * pD} };
	}
	else
		return{ false,0,{ 0,0 },{ 0,0 } };
}

CollisionData mtv_circle_ray(const circle & a, const ray & b)
{
	if (iTest_circle_ray(a, b))
	{
		vec2 c = b.p + b.d * clampf(dot((a.p - b.p), b.d), 0, b.l);
		float pD = b.l - dot(a.p - c, b.d);
		vec2 cNor = b.d;
		return{ true,pD,{-cNor},{pD * -cNor} };
	}
	else
		return{ false,0,{0,0},{0,0} };
}

CollisionData mtv_ray_plane(const ray & a, const plane & b)
{
	if(iTest_ray_plane(a,b))
	{
		float pD = a.l - ray_plane_dist(a,b);
		vec2 cNor = b.n;

		return{ true,pD,{cNor},{cNor * pD} };
	}
	else
		return{ false,0,{ 0,0 },{ 0,0 } };
}

#pragma endregion

#pragma region Shape * overloads
aabb operator*(const mat3 &m, const aabb &a)
{
	vec2 omin = a.min();
	vec2 omax = a.max();

	vec2 rmin = { m.m[0][2] , m.m[1][2] };
	vec2 rmax = { m.m[0][2], m.m[1][2] };

	float p, q;

	for (unsigned j = 0; j < 2; ++j)
		for (unsigned i = 0; i < 2; ++i)
		{
			p = omin[i] * m.m[j][i];
			q = omax[i] * m.m[j][i];

			if (p > q) 
			{
				std::swap(p, q); 
			}
			rmin[j] += p;
			rmax[j] += q;
		}
	return{ (rmin + rmax) / 2, (rmax - rmin) / 2 };
}

circle operator*(const mat3 &m, const circle &a)
{
	circle ret;
	ret.p = (m * vec3(a.p.x, a.p.y, 1)).xy;

	vec3 xrad(a.r, 0, 0);
	vec3 yrad(0, a.r, 0);

	ret.r = maxf((m*xrad).mag(), (m*yrad).mag());

	return ret;

	/*vec3 re = { a.p.x, a.p.y,1 };
	re = re * m;

	vec3 xrad(a.r,0,0);
	vec3 yrad(0,a.r, 0);

	float rad = maxf((m*xrad).mag(), (m*yrad).mag());

	return{ re.xy, rad };*/
}

ray operator*(const mat3 &m, const ray &a)
{
	vec3 dir = vec3( a.d.x, a.d.y,0 ) * a.l;
	vec3 pos = { a.p.x,a.p.y,1 };

	return{ (m*pos).xy,(m*dir).xy.normal(), dir.mag() };
}

plane operator*(const mat3 &m, const plane  &a)
{
	vec3 pos = { a.p.x, a.p.y,1 };
	vec3 nor = { a.n.x,a.n.y,0 };

	//pos = m*pos;
	nor = m*nor;
	nor.normalise();
	return{ (m*pos).xy,nor.xy };
}
#pragma endregion