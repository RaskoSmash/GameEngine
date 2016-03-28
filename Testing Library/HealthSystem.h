#pragma once
#include "System.h"
#include "Time.h"

class HealthSystem : public System
{
	bool condition(Handle<Entity> i)
	{
		return i->health > -1;
	}

	void update(Handle<Entity> i)
	{
		i->health->curHealth += i->health->regenRate * Time::instance().getDeltaTime();
		if (i->health->curHealth > i->health->maxHealth)
		{
			i->health->curHealth = i->health->maxHealth;
		}
		if (i->health->curHealth <= 0)
		{
			Entity::free(i);
		}
	}
};