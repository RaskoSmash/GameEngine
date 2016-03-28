#pragma once
#include "GCData.h"

struct Health : public GCData<Health>
{
public:
	float curHealth, maxHealth, regenRate;

	Health() : curHealth(100), maxHealth(100), regenRate(.5) {}

};