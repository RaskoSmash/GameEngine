#pragma once
#include "GCData.h"
#include "MathLibrary\ShapeIntersection.h"
#include "Transform.h"

struct Collider : public GCData<Collider>
{
	enum SHAPE {e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8} shape;

	union
	{
		circle Circle;
		aabb AABB;
		ray Ray;
		plane Plane;
	};

	Collider() : shape(e_CIRCLE)
	{ Circle = {{ 0,0 }, 1}; }
};

CollisionData EvaluateCollision(const Transform &at, const Collider &ac,
								const Transform &bt, const Collider &bc);