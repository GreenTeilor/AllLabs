#pragma once
#include "Button.h"
#include "TextMessage.h"
#include <SFML/Graphics.hpp>

class MenuItem
{
private:
	Button m_button;
	TextMessage m_textMessage;
public:
	MenuItem(const Button& button, const TextMessage& textMessage);
	bool isChosen(const sf::RenderWindow& window);
	Button& getButton();
	TextMessage& getMessage();
};

