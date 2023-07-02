#include "EventIntersectsScreen.h"
bool EventIntersectsScreen::happened = false;
Ball* EventIntersectsScreen::ballPtr = NULL;
DisplaysObject* EventIntersectsScreen::standPtr = NULL;
EventIntersectsScreen::BallIntersectionType EventIntersectsScreen::ballType = EventIntersectsScreen::BallIntersectionType::NONEBALL;
EventIntersectsScreen::StandIntersectionType EventIntersectsScreen::standType = EventIntersectsScreen::StandIntersectionType::NONEPLATFORM;
