#include "Transform.h"

Transform::Transform()
	: e_parent(nullptr), scale({ 1,1 }), position({ 0,0 }), angle(0) {}

Transform::~Transform()
{
	auto t = e_children;
	for each(Transform *child in t)
		child->setParent(e_parent);

	setParent(nullptr);
}

mat3 Transform::getGlobalTransform() const
{
	return  mat3::translate(position)
			* mat3::rotate(angle)
			* mat3::scale(scale)
			* (e_parent ? e_parent->getGlobalTransform()
				: mat3::identity());
}

void Transform::setParent(Transform *a_parent)
{
	// If we have a parent, we need to be set free!
	if (e_parent)
		e_parent->e_children.remove(this);

	// If the new parent isn't null, then adopt us!
	if (a_parent)
		a_parent->e_children.push_front(this);

	// Then set the parent
	e_parent = a_parent;
}

void Transform::setPosition(const vec2 &n_pos)
{
	position = n_pos;
}

void Transform::setScale(const vec2 &n_scale)
{
	scale = n_scale;
}

void Transform::setAngle(float _angle)
{
	angle = _angle;
}

vec2 Transform::getPosition() const
{
	return position;
}

vec2 Transform::getScale() const
{
	return scale;
}

float Transform::getAngle() const
{
	return angle;
}

vec2 Transform::getRight() const
{
	return vec2::fromAngle(angle);
}

vec2 Transform::getUp() const
{
	return vec2::fromAngle(angle).perp();
}
