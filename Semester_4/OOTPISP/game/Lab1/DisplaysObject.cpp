#include "DisplaysObject.h"

DisplaysObject::DisplaysObject(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY, bool isDynamic) : m_image{ image }, m_height{ height }, m_width{ width }, m_coordinateX { coordinateX }, m_coordinateY{ coordinateY }, m_isDynamic{ isDynamic }
{
	m_image.setPosition(coordinateX, coordinateY);
	m_coordinateX1 = m_coordinateX + m_width;
	m_coordinateY1 = m_coordinateY + m_height;
}

void DisplaysObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_image);
}

void DisplaysObject::move(const int dx, const int dy)
{
	m_coordinateX += dx;
	m_coordinateY += dy;
	m_image.move(dx, dy);
}

int DisplaysObject::getCoordinateX() const
{
	return m_coordinateX;
}

int DisplaysObject::getCoordinateY() const
{
	return m_coordinateY;
}

void DisplaysObject::setCoordinateX(const int x)
{
	m_image.setPosition(x, m_image.getPosition().y);
	m_coordinateX = x;
	m_coordinateX1 = x + m_width;
}

void DisplaysObject::setCoordinateY(const int y)
{
	m_image.setPosition(m_image.getPosition().x, y);
	m_coordinateY = y;
	m_coordinateY1 = y + m_height;
}

sf::FloatRect DisplaysObject::getShape() const
{
	return m_image.getGlobalBounds();
}

bool DisplaysObject::intersects(DisplaysObject& shape) const
{
	//THIS WAS ADDED IN LAST CLASS LESSON!!!
	
	if (((m_coordinateX >= shape.m_coordinateX && shape.m_coordinateX + shape.m_width >= m_coordinateX) ||
		(m_coordinateX + m_width >= shape.m_coordinateX && m_coordinateX + m_width <= shape.m_coordinateX + shape.m_width))
		&& ((m_coordinateY >= shape.m_coordinateY && m_coordinateY <= shape.m_coordinateY + shape.m_height) ||
			(m_coordinateY + m_height <= shape.m_coordinateY + shape.m_height && m_coordinateY + m_height >= shape.m_coordinateY)))
		return true;
	return false;
	//return sf::FloatRect(coordX, coordY, width, height).intersects(objectProc.getRect());	

	//END


	//return sf::FloatRect(m_coordinateX, m_coordinateY, m_width, m_height).intersects(shape.getShape());
}

bool DisplaysObject::intersectsScreen(int height, int width) const
{
	return (m_coordinateX < 0 || /*m_coordinateY < 0* ||*/  m_coordinateX + m_width > width || m_coordinateY + m_height > height);
}

bool DisplaysObject::isDynamic() const
{
	return m_isDynamic;
}

sf::Sprite& DisplaysObject::getImage()
{
	return m_image;
}


