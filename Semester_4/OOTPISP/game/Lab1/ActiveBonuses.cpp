#include "ActiveBonuses.h"
#include "StatusBar.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

void ActiveBonuses::disactivate(Bonus::Type type, Balls& balls)
{
	m_activeBonuses.find(type)->second.isActive = false;
	m_activeBonuses.find(type)->second.m_activeTime = 0.0;
	switch (type)
	{
	case Bonus::SPEEDSLOW:
		for (Ball& ball : balls.get_balls())
		{
			//ball.setVelocityY(ball.getVelocityY() + (ball.getVelocityY() / abs(ball.getVelocityY()) * 2));
			//ball.setVelocityY(ball.getVelocityY() * 2);
			speedControl = ball.getVelocityY() * 2;
			ball.setVelocityY(speedControl);
		}
		std::cout << "!END SPEEDSLOW\n";
		break;
	case Bonus::SPEEDUP:
		for (Ball& ball : balls.get_balls())
		{
			//ball.setVelocityY(ball.getVelocityY() - (ball.getVelocityY() / abs(ball.getVelocityY()) * 2));
			//ball.setVelocityY(ball.getVelocityY() / 1.5);
			speedControl = ball.getVelocityY() / 2;
			ball.setVelocityY(speedControl);
		}
		std::cout << "!END SPEEDUP\n";
		break;
	case Bonus::OFFCOLLISIONS:
		for (Ball& ball : balls.get_balls())
			ball.enableColisions();
		std::cout << "!END OFFCOLLISIONS\n";
		break;
	case Bonus::DOWNBORDER:
		for (Ball& ball : balls.get_balls())
			ball.offBouncing();
		std::cout << "!END DOWNBORDER\n";
		break;
	case Bonus::POINTS:
		StatusBar::additionalScore += 0;
		std::cout << "!END POINTS\n";
		break;
	default:
		assert(true && "Unreachable statement reached!");
		break;
	}
}

std::string ActiveBonuses::typeToString(Bonus::Type type) const
{
	switch (type)
	{
	case Bonus::NONE: return "None";
	case Bonus::SPEEDSLOW: return "Slow speed";
	case Bonus::SPEEDUP: return "High speed";
	case Bonus::OFFCOLLISIONS: return "Off collisions";
	case Bonus::DOWNBORDER: return "Down border";
	case Bonus::POINTS: return "Points";
	default: return "Unknown";
	}
}

ActiveBonuses::ActiveBonuses()
{
	for (int i = 1; i <= 5; ++i)
	{
		m_activeBonuses.emplace(Bonus::Type(i), State{ 0.0, false });
	}
}

void ActiveBonuses::setActive(Bonus::Type type, Balls& balls)
{
	bool reactivation = false;
	if (m_activeBonuses.find(type)->second.isActive)
		reactivation = true;
	m_activeBonuses.find(type)->second.isActive = true;
	m_activeBonuses.find(type)->second.m_activeTime = 10000.0;
	switch (type)
	{
	case Bonus::SPEEDSLOW:
		if (!reactivation)
			for (Ball& ball : balls.get_balls())
			{
				//ball.setVelocityY(ball.getVelocityY() - (ball.getVelocityY() / abs(ball.getVelocityY()) * 2));
				//ball.setVelocityY(ball.getVelocityY() / 2);
				speedControl = ball.getVelocityY() / 2;
				ball.setVelocityY(speedControl);
			}
		std::cout << "SPEEDSLOW\n";
		break;
	case Bonus::SPEEDUP:
		if (!reactivation)
			for (Ball& ball : balls.get_balls())
			{
				//ball.setVelocityY(ball.getVelocityY() + (ball.getVelocityY() / abs(ball.getVelocityY()) * 2));
				//ball.setVelocityY(ball.getVelocityY() * 1.5);
				speedControl = ball.getVelocityY() * 2;
				ball.setVelocityY(speedControl);
			}
		std::cout << "SPEEDUP\n";
		break;
	case Bonus::OFFCOLLISIONS:
		for (Ball& ball : balls.get_balls())
			ball.offColisions();
		std::cout << "OFFCOLLISIONS\n";
		break;
	case Bonus::DOWNBORDER:
		for (Ball& ball : balls.get_balls())
			ball.enableBouncing();
		std::cout << "DOWNBORDER\n";
		break;
	case Bonus::POINTS:
		StatusBar::additionalScore += 10;
		std::cout << "POINTS\n";
		break;
	default:
		assert(true && "Unreachable statement reached!");
		break;
	}
}

void ActiveBonuses::tick(Balls& balls)
{
	double elapsedTime = timer.getElapsedTime().asMilliseconds();
	for (auto& bonus : m_activeBonuses)
	{
		if (bonus.second.isActive)
		{
			bonus.second.m_activeTime -= elapsedTime;
			if (bonus.second.m_activeTime <= 0)
			{
				disactivate(bonus.first, balls);
			}
		}
	}
	timer.restart();
}

void ActiveBonuses::resetTimer()
{
	timer.restart();
}

const std::map<Bonus::Type, ActiveBonuses::State>& ActiveBonuses::get_activeBonuses() const
{
	return m_activeBonuses;
}

std::map<std::string, ActiveBonuses::State> ActiveBonuses::get_bonuses() const
{
	std::map<std::string, ActiveBonuses::State> output;

	for (auto const& pair : m_activeBonuses) {
		output.emplace(std::to_string((int)pair.first), pair.second);
	}

	return output;
}

void ActiveBonuses::from_json(const std::map<std::string, ActiveBonuses::State>& map)
{
	std::map<Bonus::Type, ActiveBonuses::State> output;

	for (auto const& pair : map) {
		output.emplace((Bonus::Type)std::stoi(pair.first), pair.second);
	}

	m_activeBonuses = output;
}

void ActiveBonuses::draw(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("../fonts/Samson.ttf");
	sf::Text text{"", font, 30};
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setOutlineThickness(2);
	int currentPositionY{400}, currentPositionX{100};
	
	for (auto const& pair : m_activeBonuses)
	{
		if (pair.second.isActive && pair.first != Bonus::POINTS)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(3) << (float)pair.second.m_activeTime / 1000;
			text.setPosition(currentPositionX, currentPositionY);
			text.setString(this->typeToString(pair.first) + " " + stream.str());
			currentPositionY += 50;
			window.draw(text);
		}
	}
}