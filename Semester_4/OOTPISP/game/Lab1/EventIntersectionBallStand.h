#pragma once
#include "Ball.h"

class EventIntersectionBallStand
{
public:
	enum Type
	{
		BALL_STAND_1,
		BALL_STAND_2,
		STAND_BALL_1,
		STAND_BALL_2,
		NONE
	};
	static bool happened;
	static Type type;
	static Ball* ballPtr;
};


