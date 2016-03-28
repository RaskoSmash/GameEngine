#pragma once
#include "MathLibrary\MathLib.h"
#include <list>
#include "GCData.h"

class Transform : public GCData<Transform>
{
	Transform *e_parent;
	std::list<Transform*> e_children;
	vec2 position, scale;
	float angle;
	// Matrix3 local; Updates whenever a setter is used

public:
	Transform();
	~Transform();

	//Matrix4 version to use with drawing.
	mat3  getGlobalTransform() const;

	void  setParent  (Transform *a_parent);
	void  setPosition(const vec2 &);
	void  setScale	 (const vec2 &);
	void  setAngle	 (float _angle);

	vec2  getPosition() const;
	vec2  getScale()    const;
	float getAngle()    const;

	vec2  getRight()    const;
	vec2  getUp()		const;
};