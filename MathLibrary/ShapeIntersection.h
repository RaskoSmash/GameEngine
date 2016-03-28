#pragma once
#include "mat3.h"

struct CollisionData
{
	bool  collides;	// Colliding?
	float penDepth; // Penetration Depth
	vec2  CollNorm,	//Collision Normal
		  Mtv;		//Minimum Translation Vector
};

struct circle
{
	vec2  p;  // Position
	float r; // Radius
};

struct aabb
{
	vec2 p,			  // position
		he;			  // half-extents
	vec2 min() const; // p - he
	vec2 max() const; // p + he
};

struct ray
{
	vec2  p, // Position
		d; // Direction
	float l; // Length
};
struct plane
{
	vec2 p, // Position
		n; // Normal
};

//Used for Collider
aabb   operator*(const mat3 &m, const aabb   &a);
circle operator*(const mat3 &m, const circle &a);
ray    operator*(const mat3 &m, const ray    &a);
plane  operator*(const mat3 &m, const plane  &a);

// Some distance algorithms from the slides
float point_plane_dist(const vec2 &a, const plane &b);
float ray_plane_dist  (const ray  &a, const plane &b);

// Should also have way to access a min and max
vec2 minv (const vec2 &a, const vec2 &b);
vec2 maxv (const vec2 &a, const vec2 &b);
vec2 clampv(const vec2 &a, const vec2 &min, const vec2 &max);

float minf(float a, float b);
float maxf(float a, float b);
float clampf(float a, float min, float max);

// do the algorithms first
bool iTest_aabb			(const aabb   &a, const aabb	&b);
bool iTest_aabb_circle	(const aabb   &a, const circle	&b);
bool iTest_aabb_plane	(const aabb   &a, const plane	&b);
bool iTest_aabb_ray		(const aabb   &a, const ray		&b);
bool iTest_circle		(const circle &a, const circle	&b);
bool iTest_circle_plane (const circle &a, const plane	&b);
bool iTest_circle_ray   (const circle &a, const ray		&b);
bool iTest_ray_plane	(const ray    &a, const plane	&b);

// Calculate the Minimum Translation Vector
CollisionData mtv_aabb		   (const aabb   &a, const aabb	  &b);
CollisionData mtv_aabb_circle  (const aabb   &a, const circle &b);
CollisionData mtv_aabb_plane   (const aabb   &a, const plane  &b);
CollisionData mtv_aabb_ray	   (const aabb   &a, const ray	  &b);
CollisionData mtv_circle	   (const circle &a, const circle &b);
CollisionData mtv_circle_plane (const circle &a, const plane  &b);
CollisionData mtv_circle_ray   (const circle &a, const ray	  &b);
CollisionData mtv_ray_plane	   (const ray    &a, const plane  &b);

float distance(const vec2 &l, const vec2 &r);

/*
min						[x]
max						[x]
clamp					[x]

aabb * mat3				[x]
circle * mat3			[x]
ray * mat3				[x]
plane * mat3			[x]

point plane distance	[x]
ray plane distance		[x]

itest AABB v AABB		[x]
itest AABB v Circle		[x]
itest AABB v Plane		[x]
itest AABB v ray		[x]
itest Circle v Circle	[x]
itest Circle v Plane	[x]
itest Circle v Ray		[x]
itest Ray v Plane		[x]

mtv AABB v AABB			[x]
mtv AABB v Circle		[x]
mtv AABB v Plane		[x]
mtv AABB v ray			[x]
mtv Circle v Circle		[x]
mtv Circle v Plane		[x]
mtv Circle v Ray		[x]
mtv Ray v Plane			[x]

distance				[x]
*/