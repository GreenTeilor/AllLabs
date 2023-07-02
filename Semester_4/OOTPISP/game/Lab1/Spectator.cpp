#include "Spectator.h"
#include "EventIntersectionBallStand.h"
#include "EventIntersectionBallBlock.h"
#include "EventAddBonus.h"
#include "EventBonusRemove.h"
#include "EventIntersectsScreen.h"
#include "Ball.h"
#include "Stand.h"
#include "Game.h"
#include "EventGameOver.h"

void Spectator::listenEvents()
{
	if ((EventIntersectionBallStand::happened == true) && (EventIntersectionBallStand::type != EventIntersectionBallStand::NONE))
	{
		Ball::handleEventBallStandIntersection();
	}
	if (EventAddBonus::happened == true)
	{
		Game::handleEventAddBonus();
	}
	if (EventIntersectionBallBlock::happened == true)
	{
		Bricks::handleEventBallBlockIntersection();
	}
	if (EventIntersectsScreen::happened == true)
	{
		if (EventIntersectsScreen::ballType != EventIntersectsScreen::BallIntersectionType::NONEBALL)
		{
			Ball::handleEventScreenIntersection();
		}
		if (EventIntersectsScreen::standType != EventIntersectsScreen::StandIntersectionType::NONEPLATFORM)
		{
			Stand::handleEventScreenIntersection();
		}
	}
	if (EventBonusRemove::happened == true)
	{
		Game::handleEventRemoveBonus();
	}
	if (EventGameOver::happened == true)
	{
		Game::handleEventGameOver();
	}

}
