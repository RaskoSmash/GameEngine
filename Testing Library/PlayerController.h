#pragma once
#include "GCData.h"
#include "sfwdraw.h"

class PlayerController : public GCData<PlayerController>
{
public:
	char LEFT, RIGHT, FORWARD, BACK, SPRINT;
	float speed, turnSpeed;

	PlayerController() : LEFT('A'), RIGHT('D'), FORWARD('W'), BACK('S'), SPRINT(' '), speed(60), turnSpeed(1) {}
};