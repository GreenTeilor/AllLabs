#pragma once
#include <SFML/Graphics.hpp>

class TellPoints
{
private:
	static sf::Clock timer;
	static bool isActive;
	static double activeTime;
	static sf::Text text;
	static sf::Font font;
public:
	static void initialize();
	static void enable(int points);
	static void tick();
	static void draw(sf::RenderWindow& window);
	static void resetTimer();
};

