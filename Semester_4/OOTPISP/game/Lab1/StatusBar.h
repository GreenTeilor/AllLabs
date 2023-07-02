#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameField.h"
#include "CommonResource.h"

class StatusBar
{
public:
	static std::vector<std::string> strings;
private:
	static std::vector<sf::Text> texts;
	static sf::Clock clock;
	static int time;

public:
	static GameField* field;
	static int score, additionalScore;
	static std::string playerName;
	static std::string difficulty;
	static int ballSpeed;

	static void initialize()
	{
		//sf::Text text;
		static sf::Font font;
		clock.restart();

		sf::Text text;
		text.setFont(font);

		text.setCharacterSize(50);
		text.setOutlineThickness(2);
		text.setOutlineColor(sf::Color::Yellow);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);

		font.loadFromFile("../fonts/Samson.ttf");
		for (int i = 0; i < strings.size(); ++i)
		{
			text.setPosition(300 * (i + 1), 5);
			text.setString(strings[i]);
			texts.push_back(text);
		}
	}

	static void update()
	{
		time = clock.getElapsedTime().asSeconds();
		score = 400 - field->m_bricks.size() + additionalScore;
		//ballSpeed = CommonResource::getBallVelocityByDifficulty(difficulty); USED TO BE
		if (CommonResource::field->m_balls.size() != 0)
			ballSpeed = abs(CommonResource::field->m_balls[0].getVelocityY());
		texts[1].setString(std::to_string(time));
		texts[2].setString(std::to_string(score));
		texts[3].setString(difficulty);
		texts[4].setString(std::to_string(ballSpeed));
	}

	static void draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < texts.size(); ++i)
		{
			window.draw(texts[i]);
		}
	}
};

