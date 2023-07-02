#pragma once
#include <SFML\Graphics.hpp>

class DisplaysObject
{
protected:
	sf::Sprite m_image;
	int m_coordinateX, m_coordinateY, m_width, m_height, m_coordinateX1, m_coordinateY1;//THIS WAS ADDED IN LAST CLASS LESSON!!!(m_coordinateX1. m_coordinateX2)
	bool m_isDynamic;
	static int max(int num1, int num2)//THIS WAS ADDED IN LAST CLASS LESSON!!!
	{
		return (num1 < num2) ? num2 : num1;
	}
	static int min(int num1, int num2)//THIS WAS ADDED IN LAST CLASS LESSON!!!
	{
		return (num1 < num2) ? num1 : num2;
	}

public:
	void move(const int dx, const int dy);//Moved from protected
	DisplaysObject(const sf::Sprite& image, int height, int width, int coordinateX = 0, int coordinateY = 0, bool isDynamic = true);
	void draw(sf::RenderWindow& window) const;
	virtual void move() = 0;
	int getCoordinateX() const;
	int getCoordinateY() const;
	void setCoordinateX(const int x);
	void setCoordinateY(const int y);
	sf::FloatRect getShape() const;
	bool intersects(DisplaysObject& shape) const;
	bool intersectsScreen(int height, int width) const;
	bool isDynamic() const;
	sf::Sprite& getImage();
};

