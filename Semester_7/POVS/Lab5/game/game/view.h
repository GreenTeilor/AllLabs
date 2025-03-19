#include <SFML/Graphics.hpp>
using namespace sf;

// Добавление объекта класса вид, что является камерой игры
View view;

View setCoordToView(float x, float y)
{
	// Исключение черных полос за картой
	// Берем переданные координаты персонажа
	float tmpX = x;
	float tmpY = y;
	// Оставляем камеру на предельной координате, если она туда доехала
	// Тут можно просто поставить solid, чтобы перс просто не 
	// уходил куда не надо
	
	if (x < 640) tmpX = 640;
	//if (y < 360) tmpY = 360;
	if (y > 500) tmpY = 500;
	if (x > 1536) tmpX = 1536;


	// Берем координаты игрока и передвигаем камеру, следя за ним
	view.setCenter(tmpX,tmpY);
	// Перерисовка камеры
	return view;
}

// Скролинг карты на стрелочки
View scrollView(float time)
{
	// Если нажата правая клавиша, просто двигаем камеру на расстояние
	// Равное произмедению прошедшего время нажатия на скорость
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		view.move(0.2 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		view.move(0, 0.2 * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		view.move(-0.2 * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		view.move(0, -0.2 * time);
	}
	// Возвращение(Перерисовка камеры)
	return view;
}
