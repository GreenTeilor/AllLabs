#include "GameField.h"

int GameField::getRandomNumber(int min, int max)
{
	srand(time(NULL));
	int num = min + rand() % (max - min + 1);
	return num;
}

GameField::GameField(const sf::Sprite& standImage, const sf::Sprite& ballImage, const sf::Sprite& brickImage, const sf::Sprite& bonusSprite,
	const int bricksAmount) :
	m_stands{ Stand{standImage, (int)standImage.getLocalBounds().height, (int)standImage.getLocalBounds().width, 1980 / 2, 1060} },
	m_balls{ Ball{ballImage, (int)ballImage.getLocalBounds().height, (int)ballImage.getLocalBounds().width, 1980 / 2, 400, 7, 2} },
	m_activeBonuses{}
	//m_bricks{ Brick{brickImage, (int)brickImage.getLocalBounds().height, (int)brickImage.getLocalBounds().width} }
{
	//m_bricks.removeBrick(0);
	for (int i = 0; i < bricksAmount; ++i)
	{
		m_bricks.addBrick(Brick{ brickImage, (int)brickImage.getLocalBounds().height, (int)brickImage.getLocalBounds().width,
			((i / 10) + 1) * 43, ((i % 10) + 1) * 20 + 100, bonusSprite, (int)bonusSprite.getLocalBounds().height + 20,
			(int)bonusSprite.getLocalBounds().width, ((i / 10) + 1) * 43, ((i % 10) + 1) * 20 + 100 });
	}
}

GameField::GameField(const Stands& stands, const Balls& balls, const Bricks& bricks, const Bonuses& bonuses, const ActiveBonuses& activeBonuses) : m_stands{ stands }, m_balls{ balls }, m_bricks{ bricks }, 
	m_bonuses{ bonuses }, m_activeBonuses{ activeBonuses }
{

}