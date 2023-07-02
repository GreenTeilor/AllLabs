#pragma once
#include <SFML\Graphics.hpp>
#include "DisplaysObject.h"
#include "Bonuses.h"

class Brick : public DisplaysObject
{
public:
	Bonuses m_bonuses;
public:
	Brick(const sf::Sprite& image, int height, int width, int coordinateX, int coordinateY, const sf::Sprite& bonusImage, int bonusHeight,
		int bonusWidth, int bonuscoordinateX, int bonuscoordinateY);
	Brick();
	void drawBonuses(sf::RenderWindow& window);
	Bonus::Type getBonusType() const;
	virtual void move() override;
	bool operator==(const Brick& brick);
	//Bonus* getOneBonus();
};

