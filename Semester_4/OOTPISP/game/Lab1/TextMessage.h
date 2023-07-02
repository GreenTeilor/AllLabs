#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "DisplaysObject.h"

class TextMessage: public DisplaysObject
{
private:
	sf::Text m_displayText;
	bool m_isShow;
public:
	TextMessage(const sf::Sprite& image, int height, int width, const sf::Text& displayText, int coordinateX = 0, int coordinateY = 0, bool isShow = true);
	void showText(sf::RenderWindow& window) const;
	virtual void move() override;
	sf::Text& getText();
};

