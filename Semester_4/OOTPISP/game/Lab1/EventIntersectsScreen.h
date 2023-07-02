#pragma once
#include "Ball.h"
#include "DisplaysObject.h"
class EventIntersectsScreen
{
public:
	enum BallIntersectionType
	{
		HORIZONTAL,
		VERTICAL,
		NONEBALL
	};
	enum StandIntersectionType
	{
		LEFT,
		RIGHT,
		NONEPLATFORM
	};
	static bool happened;
	static Ball* ballPtr;
	static DisplaysObject* standPtr;
	static BallIntersectionType ballType;
	static StandIntersectionType standType;
};

