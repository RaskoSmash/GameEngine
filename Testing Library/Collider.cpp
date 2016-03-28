#include "Collider.h"

CollisionData EvaluateCollision(const Transform & at, const Collider & ac, const Transform & bt, const Collider & bc)
{
	Transform t_lhs = at;
	Transform t_rhs = bt;
	Collider lhs = ac;
	Collider rhs = bc;

	if (lhs.shape > rhs.shape)
	{
		std::swap(lhs, rhs);
		std::swap(t_lhs, t_rhs);
	}

	CollisionData cd;

	switch (lhs.shape | rhs.shape)
	{
	case Collider::e_CIRCLE:
		cd = mtv_circle(t_lhs.getGlobalTransform() * lhs.Circle,
						t_rhs.getGlobalTransform() * rhs.Circle);
		break;
	case Collider::e_CIRCLE | Collider::e_AABB:
		cd = mtv_aabb_circle(t_rhs.getGlobalTransform() * rhs.AABB,
							 t_lhs.getGlobalTransform() * lhs.Circle);
		break;
	case Collider::e_CIRCLE | Collider::e_RAY:
		cd = mtv_circle_ray(t_lhs.getGlobalTransform() * lhs.Circle, 
							t_rhs.getGlobalTransform() * rhs.Ray);
		break;
	case Collider::e_CIRCLE | Collider::e_PLANE:
		cd = mtv_circle_plane(t_lhs.getGlobalTransform() * lhs.Circle,
							  t_rhs.getGlobalTransform() * rhs.Plane);
		break;
	case Collider::e_AABB:
		cd = mtv_aabb(t_lhs.getGlobalTransform() * lhs.AABB,
					  t_rhs.getGlobalTransform() * rhs.AABB);
		break;
	case Collider::e_AABB | Collider::e_RAY:
		cd = mtv_aabb_ray(t_lhs.getGlobalTransform() * lhs.AABB,
						  t_rhs.getGlobalTransform() * rhs.Ray);
		break;
	case Collider::e_AABB | Collider::e_PLANE:
		cd = mtv_aabb_plane(t_lhs.getGlobalTransform() * lhs.AABB,
							t_rhs.getGlobalTransform() * rhs.Plane);
		break;
	case Collider::e_RAY | Collider::e_PLANE:
		cd = mtv_ray_plane(t_lhs.getGlobalTransform() * lhs.Ray,
						   t_rhs.getGlobalTransform() * rhs.Plane);
		break;
	}
	return cd;
}
