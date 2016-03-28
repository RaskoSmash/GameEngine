#pragma once
#include "CollisionDetection.h"

class StaticResolution : public CollisionSystem
{
	bool condition(Collision c)
	{
		return c.first->rigidbody > -1 && c.second->rigidbody < 0 ||
			c.first->rigidbody <  0 && c.second->rigidbody > -1;
	}

	void update(Collision c)
	{
		auto &lhs = c.first;
		auto &rhs = c.second;

		// if they're both valid and this collision meets the reqs.
		if (lhs->isValid() && condition(c) &&
			rhs->isValid())
		{
			vec2 pos = { 0,0 };
			if (c.first->rigidbody > -1)
			{
				pos = c.first->transform->getPosition() + c.collision.Mtv;
				c.first->transform->setPosition(pos);
			}
			else if (c.second->rigidbody > -1)
			{
				pos = c.second->transform->getPosition() + c.collision.Mtv;
				c.second->transform->setPosition(pos);
			}
		}
	}
};