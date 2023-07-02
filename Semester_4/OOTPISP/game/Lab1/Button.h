#pragma once
#include <SFML/Graphics.hpp>
#include "DisplaysObject.h"

class Button: public DisplaysObject
{
private:
	bool m_isShow;
public:
	Button(const sf::Sprite& image, int height, int width, int coordinateX = 0, int coordinateY = 0, bool isDynamic = true, bool isShow = true);
	bool isPressed(const sf::RenderWindow& window);
	virtual void move() override;
};

