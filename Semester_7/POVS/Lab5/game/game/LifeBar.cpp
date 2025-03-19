#include "LifeBar.h"

LifeBar::LifeBar()
{
	image.loadFromFile("images/life.png");
	image.createMaskFromColor(Color(52, 52, 52));


	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(9, 5, 32, 168));
	// Закрашивающий прямоугольник
	bar.setFillColor(Color(38, 43, 43));
	max = 100;
	bar.setSize(Vector2f(0, 0));
}

void LifeBar::update(int k)
{
	if (k > 0)
		if (k < max)
			// Установка новых размеров прямоугольника
			bar.setSize(Vector2f(20, (max - k) * 12 / 10));
}

void LifeBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	bar.setPosition(center.x - size.x / 2 + 17, center.y - size.y / 2 + 18);

	// Рисование полоски здоровья и поверх ее прямоугольник
	window.draw(s);
	window.draw(bar);
}

