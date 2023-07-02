#include "Brick.h"
#include "CommonResource.h"

Brick::Brick(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY, const sf::Sprite& bonusImage, int bonusHeight,
	int bonusWidth, int bonuscoordinateX, int bonuscoordinateY) : DisplaysObject(image, height, width, coordinateX, coordinateY)
{
	m_bonuses = Bonuses(Bonus(CommonResource::bonusSprite, bonusHeight, bonusWidth, bonuscoordinateX, bonuscoordinateY, Bonus::Type::NONE));
	m_isDynamic = false;
}

Brick::Brick() : DisplaysObject(CommonResource::brickSprite, CommonResource::brickScales.height, CommonResource::brickScales.width)
{
	m_bonuses = Bonuses(Bonus(CommonResource::bonusSprite, CommonResource::bonusScale.height, CommonResource::bonusScale.width, 0, 0, Bonus::Type::NONE));
	m_isDynamic = false;
}

//Bonus* Brick::getOneBonus()
//{
//	return &(m_bonuses.getBonus(0));
//}

Bonus::Type Brick::getBonusType() const
{
	return m_bonuses.getBonus(0).getType();
}

void Brick::move()
{

}

void Brick::drawBonuses(sf::RenderWindow& window)
{
	m_bonuses[0].draw(window);
}

bool Brick::operator==(const Brick& brick)
{
	return m_coordinateX == brick.m_coordinateX && m_coordinateY == brick.m_coordinateY;
}
