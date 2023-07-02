#include "CommonResource.h"
GameField* CommonResource::field{ new GameField{sf::Sprite{}, sf::Sprite{}, sf::Sprite{},sf::Sprite{}, 0} };
sf::Sprite CommonResource::standSprite{};
sf::Sprite CommonResource::ballSprite{};
sf::Sprite CommonResource::brickSprite{};
sf::Sprite CommonResource::bonusSprite{};
CommonResource::Scales CommonResource::standScales{};
CommonResource::Scales CommonResource::ballScales{};
CommonResource::Scales CommonResource::brickScales{};
CommonResource::Scales CommonResource::bonusScale{};
CommonResource::Scales CommonResource::windowScales{ 1080, 1920 };
std::string CommonResource::difficulty{ "easy" };

void CommonResource::initialize()
{
	static sf::Texture standTexture;
	static sf::Texture ballTexture;
	static sf::Texture brickTexture;
	static sf::Texture bonusTexture;
	standTexture.loadFromFile("../images/stand2.jpg");
	ballTexture.loadFromFile("../images/ball1.png");
	brickTexture.loadFromFile("../images/block01.png");
	bonusTexture.loadFromFile("../images/block02.png");
	CommonResource::ballSprite = sf::Sprite{ ballTexture };
	CommonResource::ballScales = { (int)ballSprite.getLocalBounds().height, (int)ballSprite.getLocalBounds().width };
	CommonResource::standSprite = sf::Sprite{ standTexture };
	CommonResource::standScales = { (int)standSprite.getLocalBounds().height, (int)standSprite.getLocalBounds().width };
	CommonResource::brickSprite = sf::Sprite{ brickTexture };
	CommonResource::brickScales = { (int)brickSprite.getLocalBounds().height, (int)brickSprite.getLocalBounds().width };

	CommonResource::bonusSprite = sf::Sprite{ bonusTexture };
	CommonResource::bonusScale = { (int)bonusSprite.getLocalBounds().height, (int)bonusSprite.getLocalBounds().width };
}

int CommonResource::getBallVelocityByDifficulty(std::string difficulty)
{
	if (difficulty == "easy")
	{
		return 2;
	}
	else if (difficulty == "medium")
	{
		return 4;
	}
	else if (difficulty == "hard")
	{
		return 6;
	}
	else if (difficulty == "insane")
	{
		return 8;
	}
	else if (difficulty == "god")
	{
		return 10;
	}
}
