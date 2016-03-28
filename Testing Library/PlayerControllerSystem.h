#pragma once

#include "System.h"
#include "Input.h"
#include "Time.h"
//#include "Factory.h"

class PlayerControllerSystem : public System
{
	bool condition(Handle<Entity> i)
	{
		return i->rigidbody  > -1 &&
			i->transform  > -1 &&
			i->controller > -1;
	}

	void update(Handle<Entity> i)
	{
		auto  &input = Input::instance();
		auto  &c = *i->controller;
		auto  &r = *i->rigidbody;
		float dt = Time::instance().getDeltaTime();

		if (input.getKey(c.LEFT))
			r.addForce(i->transform->getRight() * -c.speed);

		if (input.getKey(c.RIGHT))
			r.addForce(i->transform->getRight() * c.speed);
//			r.addTorque(-c.turnSpeed);

		if (input.getKey(c.FORWARD))
			r.addForce(i->transform->getUp() * c.speed);

		if (input.getKey(c.BACK))
			r.addForce(i->transform->getUp() * -c.speed);

		if (input.getKey('X'))
		{
			i->health->curHealth -= 100 * dt;
			//Factory::makeBullet(i->transform->getPosition(), i->transform->getUp());
		}
	}

};

//TODO: make factory