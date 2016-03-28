#pragma once
#include "MathLibrary\MathLib.h"
#include "Transform.h"

class RigidBody : public GCData<RigidBody>
{
public:
	vec2 velocity, acceleration, force;
	float mass, drag,
		av, ac, torque;

	RigidBody();
	void addForce(vec2 &a);
	void addTorque(float a);
	void integrate(Transform *t, float dt);
};