#pragma once
#include "Stands.h"
#include "Balls.h"
#include "Bricks.h"
#include <SFML/Graphics.hpp>
#include "ActiveBonuses.h"


class GameField
{
public:
	Stands m_stands;
	Balls m_balls;
	Bricks m_bricks;
	Bonuses m_bonuses;
	ActiveBonuses m_activeBonuses;

	int getRandomNumber(int min, int max);

public:
	GameField(const sf::Sprite& standImage, const sf::Sprite& ballImage, const sf::Sprite& brickImage, const sf::Sprite& bonusSprite,
		const int bricksAmount = 400);
	GameField(const Stands& stands, const Balls& balls, const Bricks& bricks, const Bonuses& bonuses, const ActiveBonuses& activeBonuses);
};

