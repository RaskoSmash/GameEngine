#pragma once
#include "GCData.h"

struct Stamina : public GCData<Stamina>
{
public:
	float curStam, maxStam, regenRate, decreaseRate, minStart;

	Stamina() : curStam(100), maxStam(100), regenRate(5), decreaseRate(15), minStart(10) {}

};