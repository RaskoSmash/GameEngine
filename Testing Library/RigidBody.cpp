#include "RigidBody.h"
#include "Transform.h"

RigidBody::RigidBody()	:
	acceleration({ 0,0 }), velocity({0,0}), mass(1),
	force({ 0,0 }), drag(.5f), torque(0), av(0), ac(0) {}

void RigidBody::addForce(vec2 & a)
{
	force = force + a;
}

void RigidBody::addTorque(float a)
{
	torque += a;
}

void RigidBody::integrate(Transform * t, float dt)
{
	acceleration = force / mass;
	velocity = velocity + acceleration * dt;
	t->setPosition(t->getPosition() + dt * velocity);

	velocity = velocity - drag * velocity * dt;
	force = { 0,0 };

	ac = torque / mass;
	av += ac * dt;
	t->setAngle(t->getAngle() + av*dt);
	torque = 0;
}
