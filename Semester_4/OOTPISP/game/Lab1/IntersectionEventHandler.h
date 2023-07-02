#pragma once
#include "DisplaysObject.h"
#include "Ball.h"
#include "Stand.h"
#include <vector>
#include "Bricks.h"
#include "CommonResource.h"
#include <SFML/Graphics.hpp>
#include "EventIntersectionBallStand.h"
#include "EventIntersectionBallBlock.h"
#include "EventAddBonus.h"
#include "EventBonusRemove.h"
#include "EventIntersectsScreen.h"
#include "Spectator.h"

class IntersectionEventHandler
{
private:
	IntersectionEventHandler()
	{

	}

public:
	static Bricks* bricks;
	static Bonuses* bonuses;
	static std::vector<DisplaysObject*>* shapes;

	static void intersection(DisplaysObject* shape1, DisplaysObject* shape2)
	{
		Ball* ball1 = dynamic_cast<Ball*>(shape1);
		Ball* ball2 = dynamic_cast<Ball*>(shape2);
		Brick* brick1 = dynamic_cast<Brick*>(shape1);
		Brick* brick2 = dynamic_cast<Brick*>(shape2);
		Bonus* bonus1 = dynamic_cast<Bonus*>(shape1);
		Bonus* bonus2 = dynamic_cast<Bonus*>(shape2);
		Stand* stand1 = dynamic_cast<Stand*>(shape1);
		Stand* stand2 = dynamic_cast<Stand*>(shape2);

		if (shape1->intersects(*shape2))
		{
			if (dynamic_cast<Ball*>(shape1) != NULL && !dynamic_cast<Bonus*>(shape2) && ball1->isCollisionable() || (dynamic_cast<Stand*>(shape2) != NULL && dynamic_cast<Ball*>(shape1) != NULL))
			{
				if (!Ball(sf::Sprite(), 36, 36, shape1->getCoordinateX() - ball1->getVelocityX(), shape1->getCoordinateY(), ball1->getVelocityX(), ball1->getVelocityY()).intersects(*shape2))
				{
					EventIntersectionBallStand::happened = true;
					EventIntersectionBallStand::type = EventIntersectionBallStand::Type::BALL_STAND_1;
					EventIntersectionBallStand::ballPtr = ball1;
				}
				else if (!Ball(sf::Sprite(), 36, 36, shape1->getCoordinateX(), shape1->getCoordinateY() - ball1->getVelocityY(), ball1->getVelocityX(), ball1->getVelocityY()).intersects(*shape2))
				{
					EventIntersectionBallStand::happened = true;
					EventIntersectionBallStand::type = EventIntersectionBallStand::Type::BALL_STAND_2;
					EventIntersectionBallStand::ballPtr = ball1;
				}
			}
			else if (dynamic_cast<Ball*>(shape2) != NULL && !dynamic_cast<Bonus*>(shape1) && ball2->isCollisionable() || (dynamic_cast<Stand*>(shape1) != NULL && dynamic_cast<Ball*>(shape2) != NULL))
			{
				if (!Ball(sf::Sprite(), 36, 36, shape2->getCoordinateX() - ball2->getVelocityX(), shape2->getCoordinateY(), ball2->getVelocityX(), ball2->getVelocityY()).intersects(*shape1))
				{
					EventIntersectionBallStand::happened = true;
					EventIntersectionBallStand::type = EventIntersectionBallStand::Type::STAND_BALL_1;
					EventIntersectionBallStand::ballPtr = ball2;

				}
				else if (!Ball(sf::Sprite(), 36, 36, shape2->getCoordinateX(), shape2->getCoordinateY() - ball2->getVelocityY(), ball2->getVelocityX(), ball2->getVelocityY()).intersects(*shape1))
				{
					EventIntersectionBallStand::happened = true;
					EventIntersectionBallStand::type = EventIntersectionBallStand::Type::STAND_BALL_2;
					EventIntersectionBallStand::ballPtr = ball2;

				}
			}
			Spectator::listenEvents();


			if (brick1 != NULL && ball2 != NULL)
			{
				for (int i = 0; i < bricks->size(); ++i)
				{
					if ((*bricks)[i] == *brick1)
					{
						EventAddBonus::happened = true;
						EventAddBonus::bonusesPtr = bonuses;
						EventAddBonus::bricksPtr = bricks;
						EventAddBonus::index = i;
						//--------------------------------------
						EventIntersectionBallBlock::happened = true;
						EventIntersectionBallBlock::bricksPtr = bricks;
						EventIntersectionBallBlock::index = i;
						Spectator::listenEvents();
					}
				}
			}
			else if (brick2 != NULL && ball1 != NULL)
			{
				for (int i = 0; i < bricks->size(); ++i)
				{
					if ((*bricks)[i] == *brick2)
					{
						EventAddBonus::happened = true;
						EventAddBonus::bonusesPtr = bonuses;
						EventAddBonus::bricksPtr = bricks;
						EventAddBonus::index = i;
						//--------------------------------------
						EventIntersectionBallBlock::happened = true;
						EventIntersectionBallBlock::bricksPtr = bricks;
						EventIntersectionBallBlock::index = i;
						Spectator::listenEvents();
					}
				}
			}

			if (stand1 != NULL && bonus2 != NULL)
			{
				for (int i = 0; i < bonuses->size(); ++i)
				{
					if ((*bonuses)[i] == *bonus2)
					{
						CommonResource::field->m_activeBonuses.setActive(bonus2->getType(), CommonResource::field->m_balls);
						//-----------------------------------------
						EventBonusRemove::happened = true;
						EventBonusRemove::bonusesPtr = bonuses;
						EventBonusRemove::index = i;
						Spectator::listenEvents();
					}
				}
			}
			else if (stand2 != NULL && bonus1 != NULL)
			{
				for (int i = 0; i < bonuses->size(); ++i)
				{
					if ((*bonuses)[i] == *bonus1)
					{
						CommonResource::field->m_activeBonuses.setActive(bonus1->getType(), CommonResource::field->m_balls);
						//----------------------------------
						EventBonusRemove::happened = true;
						EventBonusRemove::bonusesPtr = bonuses;
						EventBonusRemove::index = i;
						Spectator::listenEvents();
					}
				}
			}


		}
	}

	static void screenIntersection(DisplaysObject* shape)
	{
		Ball* ball = dynamic_cast<Ball*>(shape);
		Stand* stand = dynamic_cast<Stand*>(shape);
		if (dynamic_cast<Ball*>(shape) != NULL)
		{
			EventIntersectsScreen::ballPtr = ball;
			EventIntersectsScreen::happened = true;
			if (ball->getCoordinateX() < 0 || ball->getCoordinateX() + 36 > 1920)
				EventIntersectsScreen::ballType = EventIntersectsScreen::BallIntersectionType::HORIZONTAL;
			else if (ball->getCoordinateY() < 110 || (ball->getCoordinateY() + 36 > 1080 && ball->isBouncing()))
				EventIntersectsScreen::ballType = EventIntersectsScreen::BallIntersectionType::VERTICAL;
		}
		if (dynamic_cast<Stand*>(shape) != NULL)
		{
			EventIntersectsScreen::standPtr = shape;
			EventIntersectsScreen::happened = true;
			if (stand->getCoordinateX() < 0)
			{
				EventIntersectsScreen::standType = EventIntersectsScreen::StandIntersectionType::LEFT;
			}
			else if (stand->getCoordinateX() + 144 > 1920)
			{
				EventIntersectsScreen::standType = EventIntersectsScreen::StandIntersectionType::RIGHT;
			}
		}
		Spectator::listenEvents();
	}




};

