#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Keyboard::Key m_leftControlKey;
	sf::Keyboard::Key m_rightControlKey;

public:
	Player(sf::Keyboard::Key leftControlKey = sf::Keyboard::Left, sf::Keyboard::Key rightControlKey = sf::Keyboard::Right);
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
};

