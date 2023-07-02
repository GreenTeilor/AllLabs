#include "MenuItem.h"

MenuItem::MenuItem(const Button& button, const TextMessage& textMessage) : m_button{ button }, m_textMessage{ textMessage }
{

}

bool MenuItem::isChosen(const sf::RenderWindow& window)
{
	return m_button.isPressed(window);
}

Button& MenuItem::getButton()
{
	return m_button;
}

TextMessage& MenuItem::getMessage()
{
	return m_textMessage;
}