#include "TellPoints.h"

sf::Clock TellPoints::timer{};
bool TellPoints::isActive{ false };
double TellPoints::activeTime{ 0.0 };
sf::Font TellPoints::font{};
sf::Text TellPoints::text{};

void TellPoints::initialize()
{
	font.loadFromFile("../fonts/Samson.ttf");
	text = sf::Text{ "+10 points", font, 30 };
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setOutlineThickness(2);
	text.setPosition(1700, 400);
}

void TellPoints::enable(int points)
{
	isActive = true;
	activeTime = 1000.0;
	text.setString("+" + std::to_string(points) + " points");
}

void TellPoints::tick()
{
	double elapsedTime = timer.getElapsedTime().asMilliseconds();
	activeTime -= elapsedTime;
	if (activeTime <= 0)
	{
		activeTime = 0.0;
		isActive = false;
	}
	timer.restart();
}

void TellPoints::draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(text);
	}	
}

void TellPoints::resetTimer()
{
	timer.restart();
}
