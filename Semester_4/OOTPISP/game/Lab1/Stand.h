#pragma once
#include "DisplaysObject.h"
#include "Player.h"

class Stand: public DisplaysObject
{
private:
	Player player;
public:
	Stand(const sf::Sprite& image, int height, int width, int coordinateX = 0, int coordinateY = 0);
	Stand();
	virtual void move() override;
	static void handleEventScreenIntersection();
};

