#pragma once
#include "GameField.h"

class CommonResource
{
public:
	struct Scales
	{
		int height;
		int width;
	};

	static GameField* field;
	static sf::Sprite standSprite;
	static Scales standScales;
	static sf::Sprite ballSprite;
	static Scales ballScales;
	static sf::Sprite brickSprite;
	static Scales brickScales;
	static sf::Sprite bonusSprite;
	static Scales bonusScale;
	static Scales windowScales;
	static std::string difficulty;
	static void initialize();
	static int getBallVelocityByDifficulty(std::string difficulty);
};

