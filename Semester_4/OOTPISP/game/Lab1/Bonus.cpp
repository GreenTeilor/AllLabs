#include "Bonus.h"
#include "SFML/Graphics.hpp"
#include "CommonResource.h"

Bonus::Bonus(const sf::Sprite& bonusImage, int bonusHeight,
	int bonusWidth, int bonuscoordinateX, int bonuscoordinateY, const Type& type) : DisplaysObject(bonusImage, bonusHeight, bonusWidth, bonuscoordinateX, bonuscoordinateY), m_type{ type }
{

}

Bonus::Bonus(): DisplaysObject{ CommonResource::bonusSprite, CommonResource::bonusScale.height, CommonResource::bonusScale.width }
{
	
}

void Bonus::cast()
{
	move();
}

void Bonus::changeCast()
{
	if (m_type != NONE)
		canCast = true;
}

void Bonus::setType(Type type)
{
	m_type = type;
}

Bonus::Type Bonus::getType() const
{
	return m_type;
}

void Bonus::draw(sf::RenderWindow& window)
{
	if ((canCast == true) && (m_type != NONE))
	{
		DisplaysObject::draw(window);
	}
}

void Bonus::move()
{
	if ((canCast == true) && (m_type != NONE))
	{
		DisplaysObject::move(0, 2);
	}
}

bool Bonus::operator==(const Bonus& bonus)
{
	return m_coordinateX == bonus.m_coordinateX && m_coordinateY == bonus.m_coordinateY && bonus.m_type == m_type;
}

