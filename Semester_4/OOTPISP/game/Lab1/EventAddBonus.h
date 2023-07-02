#pragma once
#include "Bonuses.h"
#include "Bricks.h"
class EventAddBonus
{
public:
	static bool happened;
	static Bonuses* bonusesPtr;
	static Bricks* bricksPtr;
	static int index;
};

