#pragma once
#include "System.h"
#include "Time.h"
#include "Input.h"


class StaminaSystem : public System
{
	bool condition(Handle<Entity> i)
	{
		return i->stamina > -1;
	}

	void update(Handle<Entity> i)
	{
		auto &input = Input::instance();
		auto &c = *i->controller;

		if (i->stamina->curStam <= i->stamina->maxStam && !(input.getKey(c.SPRINT)))
		{
			i->stamina->curStam += i->stamina->regenRate * Time::instance().getDeltaTime();
			if (i->stamina->curStam > i->stamina->maxStam)
			{
				i->stamina->curStam = i->stamina->maxStam;
			}
		}
		else if (input.getKey(c.SPRINT) && i->stamina->curStam > 0 && i->stamina->curStam > i->stamina->minStart)
		{
			i->rigidbody->velocity *= 1.05;
			i->stamina->curStam -= i->stamina->decreaseRate * Time::instance().getDeltaTime();
		}
	}
};