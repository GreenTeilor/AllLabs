#include "Ball.h"
#include "CommonResource.h"
#include "EventIntersectionBallStand.h"
#include "EventIntersectsScreen.h"

Ball::Ball(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY, int velocityX, int velocityY) : DisplaysObject(image, height, width, coordinateX, coordinateY), m_velocityX{ velocityX }, m_velocityY{ velocityY }, 
		m_areCollisionsOn{ true }, m_isBouncing{ false }
{

}

Ball::Ball() : DisplaysObject{ CommonResource::ballSprite, CommonResource::ballScales.height, CommonResource::ballScales.width }, m_areCollisionsOn{ true }, m_isBouncing{ false }
{

}

int Ball::getVelocityX() const
{
	return m_velocityX;
}

int Ball::getVelocityY() const
{
	return m_velocityY;
}

void Ball::setVelocityX(const int velocityX)
{
	m_velocityX = velocityX;
}

void Ball::setVelocityY(const int velocityY)
{
	m_velocityY = velocityY;
}

void Ball::move()
{
	DisplaysObject::move(m_velocityX, m_velocityY);
}

void Ball::enableColisions()
{
	m_areCollisionsOn = true;
}

void Ball::offColisions()
{
	m_areCollisionsOn = false;
}

void Ball::enableBouncing()
{
	m_isBouncing = true;
}

void Ball::offBouncing()
{
	m_isBouncing = false;
}

bool Ball::isCollisionable()
{
	return m_areCollisionsOn;
}

void Ball::handleEventBallStandIntersection()
{
	if (EventIntersectionBallStand::ballPtr != NULL)
	{
		switch (EventIntersectionBallStand::type)
		{
		case EventIntersectionBallStand::BALL_STAND_1: {
			EventIntersectionBallStand::ballPtr->setVelocityX(-EventIntersectionBallStand::ballPtr->getVelocityX());
			break;
		}
		case EventIntersectionBallStand::BALL_STAND_2: {
			EventIntersectionBallStand::ballPtr->setVelocityY(-EventIntersectionBallStand::ballPtr->getVelocityY());
			break;
		}
		case EventIntersectionBallStand::STAND_BALL_1: {
			EventIntersectionBallStand::ballPtr->setVelocityY(-EventIntersectionBallStand::ballPtr->getVelocityY());
			break;
		}
		case EventIntersectionBallStand::STAND_BALL_2: {
			EventIntersectionBallStand::ballPtr->setVelocityY(-EventIntersectionBallStand::ballPtr->getVelocityY());
			break;
		}
		}
		EventIntersectionBallStand::happened = false;
		EventIntersectionBallStand::type = EventIntersectionBallStand::NONE;
		EventIntersectionBallStand::ballPtr = NULL;
	}
}

void Ball::handleEventScreenIntersection()
{
	if (EventIntersectsScreen::ballPtr != NULL)
	{
		if (EventIntersectsScreen::ballType == EventIntersectsScreen::HORIZONTAL)
		{
			EventIntersectsScreen::ballPtr->setVelocityX(-EventIntersectsScreen::ballPtr->getVelocityX());
		}
		else
		{
			EventIntersectsScreen::ballPtr->setVelocityY(-EventIntersectsScreen::ballPtr->getVelocityY());
		}
		EventIntersectsScreen::happened = false;
		EventIntersectsScreen::ballType = EventIntersectsScreen::BallIntersectionType::NONEBALL;
		EventIntersectsScreen::ballPtr = NULL;
	}
}

bool Ball::isBouncing()
{
	return m_isBouncing;
}

bool Ball::operator==(const Ball& ball)
{
	return m_coordinateX == ball.m_coordinateX && m_coordinateY == ball.m_coordinateY && m_velocityX == ball.m_velocityX && m_velocityY == ball.m_velocityY;
}
