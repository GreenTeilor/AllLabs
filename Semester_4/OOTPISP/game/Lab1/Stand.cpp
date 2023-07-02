#include "Stand.h"
#include "CommonResource.h"
#include "EventIntersectsScreen.h"

Stand::Stand(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY) : DisplaysObject{ image, height, width, coordinateX, coordinateY },
player{}
{

}

Stand::Stand() : DisplaysObject{ CommonResource::standSprite, CommonResource::standScales.height, CommonResource::standScales.width }
{

}

void Stand::move()
{
	if (player.isLeftKeyPressed())
		DisplaysObject::move(-12, 0);
	if (player.isRightKeyPressed())
		DisplaysObject::move(12, 0);
}

void Stand::handleEventScreenIntersection()
{
	if (EventIntersectsScreen::standPtr != NULL)
	{
		if (EventIntersectsScreen::standType == EventIntersectsScreen::LEFT)
		{
			EventIntersectsScreen::standPtr->move(12, 0);
		}
		else
		{
			EventIntersectsScreen::standPtr->move(-12, 0);
		}
		EventIntersectsScreen::happened = false;
		EventIntersectsScreen::standType = EventIntersectsScreen::StandIntersectionType::NONEPLATFORM;
		EventIntersectsScreen::standPtr = NULL;
	}
}