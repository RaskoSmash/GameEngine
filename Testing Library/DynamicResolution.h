#pragma once
#include "CollisionDetection.h"

class DynamicResolution : public CollisionSystem
{
	bool condition(Collision c)
	{
		return c.first->rigidbody > -1 && c.second->rigidbody > -1;
	}

	void update(Collision c)
	{
		auto &lhs = c.first;
		auto &rhs = c.second;

		// if they're both valid and this collision meets the reqs.
		if (lhs->isValid() && condition(c) &&
			rhs->isValid())
		{
			vec2 p1 = lhs->transform->getPosition() + c.collision.Mtv / 2;
			vec2 p2 = rhs->transform->getPosition() - c.collision.Mtv / 2;

			c.first->transform->setPosition(p1);
			c.second->transform->setPosition(p2);

			if (lhs->health > -1)
			{
				c.first->health->curHealth -= 100 * Time::instance().getDeltaTime();
			}
			else if (rhs->health > -1)
			{
				c.second->health->curHealth -= 100 * Time::instance().getDeltaTime();
			}

			std::swap(c.first->rigidbody->velocity, c.second->rigidbody->velocity);
		}
	}
};