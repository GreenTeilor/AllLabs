#include "TextMessage.h"

TextMessage::TextMessage(const sf::Sprite& image, int height, int width, const sf::Text& displayText, int coordinateX, int coordinateY, bool isShow) : DisplaysObject{ image, height, width, coordinateX, coordinateY }, m_displayText{ displayText }, m_isShow{ isShow }
{
	m_displayText.setPosition(coordinateX, coordinateY);
}

void TextMessage::showText(sf::RenderWindow& window) const
{
	window.draw(m_image);
	window.draw(m_displayText);
}

void TextMessage::move()
{

}

sf::Text& TextMessage::getText()
{
	return m_displayText;
}