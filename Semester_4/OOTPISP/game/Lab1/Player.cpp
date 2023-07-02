#include "Player.h"

Player::Player(sf::Keyboard::Key leftControlKey, sf::Keyboard::Key rightControlKey) :
	m_leftControlKey{ leftControlKey }, m_rightControlKey{ rightControlKey }
{

}

bool Player::isLeftKeyPressed()
{
	return sf::Keyboard::isKeyPressed(m_leftControlKey);
}

bool Player::isRightKeyPressed()
{
	return sf::Keyboard::isKeyPressed(m_rightControlKey);
}