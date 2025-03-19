#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;

	LifeBar();

	// k - текущее здоровье
	void update(int k);

	void draw(RenderWindow& window);

};
