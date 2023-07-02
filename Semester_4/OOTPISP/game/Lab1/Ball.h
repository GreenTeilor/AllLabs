#pragma once
#include <SFML\Graphics.hpp>
#include "DisplaysObject.h"

class Ball: public DisplaysObject
{
private:
	int m_velocityX, m_velocityY;
	bool m_areCollisionsOn, m_isBouncing;
public:
	Ball(const sf::Sprite& image, int height, int width, int coordinateX = 0, int coordinateY = 0, int velocityX = 0, int velocityY = 0);
	Ball();
	int getVelocityX() const;
	int getVelocityY() const;
	void setVelocityX(const int velocityX);
	void setVelocityY(const int velocityY);
	virtual void move() override;
	void enableColisions();
	void offColisions();
	void enableBouncing();
	void offBouncing();
	bool isCollisionable();
	bool isBouncing();
	bool operator==(const Ball& ball);
	static void handleEventBallStandIntersection();
	static void handleEventScreenIntersection();
};

