#include <SFML/Graphics.hpp>

using namespace sf;

void setSpriteSize(Sprite& sprite, const float width, const float height)
{
	sf::Vector2f targetSize(width, height); //Size in pixels
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
}

Sprite getTile(const Texture& tilesImage, const int tileNum)
{

	Sprite tile{ tilesImage, IntRect((tileNum % 6) * 74, (tileNum / 6) * 97, 75, 95) };

	setSpriteSize(tile, 200.0f, 262.0f);
	tile.setPosition(350.0f, 300.0f);
	return tile;
}

int main()
{
	RenderWindow window(VideoMode(900, 600), "Graphics!");
	Text text;
	Font font;
	font.loadFromFile("..//fonts//rusFont.ttf");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setPosition(120, 150);
	text.setFillColor(Color::Black);
	Texture images;
	images.loadFromFile("..//images//elephant_faces.jpg");
	Sprite image = getTile(images, 0);
	float currentFrame{ 0.0f };
	Clock clock;

	while (window.isOpen())
	{
		float time{ static_cast<float>(clock.getElapsedTime().asMicroseconds()) };
		clock.restart();
		time = time / 100;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{	
			currentFrame += 0.001f * time;
			if (currentFrame > 17) currentFrame -= 17;
			image = getTile(images, static_cast<int>(currentFrame));
			text.setString(L"Слон читает!");
		}
		else
		{
			text.setString(L"Слон думает...");
		}

		window.clear(Color(255, 255, 255, 255));

		window.draw(text);
		window.draw(image);

		window.display();

	}

	return 0;
}
