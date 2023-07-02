#include "Button.h"

Button::Button(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY, bool isDynamic, bool isShow) : DisplaysObject{ image, height, width, coordinateX, coordinateY, isDynamic },
m_isShow{ isShow }
{

}

bool Button::isPressed(const sf::RenderWindow& window)
{
	return false;
}

void Button::move()
{

}