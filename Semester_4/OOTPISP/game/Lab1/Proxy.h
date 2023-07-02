#pragma once
#include "Gamefield.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "json_template.h"
#include "StatusBar.h"


std::vector<std::string> getWords(std::string s)
{
	std::string word = "";
	std::vector<std::string> result;
	int i = 0;
	while (i < s.size())
	{
		if (s[i] == ' ')
		{
			result.push_back(word);
			word = "";
		}
		else
		{
			word += s[i];
		}
		++i;
	}
	result.push_back(word);
	return result;
}

class Serializator
{
public:

	static void save(GameField& field, std::string name)
	{
		/*
		std::vector<Stand> stands;
		std::vector<Ball> balls;
		std::vector<Brick> bricks;
 
		for (int i = 0; i < field.m_stands.size(); ++i) 
		{
			stands.push_back(field.m_stands[i]);
		}
		for (int i = 0; i < field.m_balls.size(); ++i)
		{
			balls.push_back(field.m_balls[i]);
		}
		for (int i = 0; i < field.m_bricks.size(); ++i)
		{
			bricks.push_back(field.m_bricks[i]);
		}
		*/
		
		nlohmann::json j{};
		j["stands"] = field.m_stands.get_stands();
		j["balls"] = field.m_balls.get_balls();
		j["bricks"] = field.m_bricks.get_bricks();
		j["bonuses"] = field.m_bonuses.get_bonuses();
		j["activeBonuses"] = field.m_activeBonuses.get_bonuses();
		j["name"] = name;
		j["dimension"] = std::to_string(CommonResource::windowScales.width) + " " + std::to_string(CommonResource::windowScales.height);
		j["difficulty"] = CommonResource::difficulty;
		j["additionalScore"] = StatusBar::additionalScore;
		
		
		std::string path{ "../save/save.json" };
		std::string path1{ "../save/save.txt" };
		std::ofstream out;
		out.open(path);
		if (!out.is_open())
		{
			std::cout << "File isn't opened!";
		}
		else
		{
			//out.write(j.dump().c_str(), sizeof(j.dump().c_str()));
			out << j;
		}
		out.close();
		out.open(path1);
		for (int i = 0; i < field.m_stands.get_stands().size(); ++i)
		{
			out << "Stand: coordinateX=" << field.m_stands.get_stands()[i].getCoordinateX() << " coordinateY=" << field.m_stands.get_stands()[i].getCoordinateY() << "\n";
		}
		for (int i = 0; i < field.m_balls.get_balls().size(); ++i)
		{
			out << "Ball: coordinateX=" << field.m_balls.get_balls()[i].getCoordinateX() << " coordinateY=" << field.m_balls.get_balls()[i].getCoordinateY() << " speedX=" << field.m_balls.get_balls()[i].getVelocityX() << " speedY=" << field.m_balls.get_balls()[i].getVelocityY() << "\n";
		}
		for (int i = 0; i < field.m_bricks.get_bricks().size(); ++i)
		{
			out << "Brick: coordinateX=" << field.m_bricks.get_bricks()[i].getCoordinateX() << " coordinateY=" << field.m_bricks.get_bricks()[i].getCoordinateY() << "\n";
		}
		for (int i = 0; i < field.m_bonuses.get_bonuses().size(); ++i)
		{
			out << "Bonus: coordinateX=" << field.m_bonuses.get_bonuses()[i].getCoordinateX() << " coordinateY=" << field.m_bonuses.get_bonuses()[i].getCoordinateY() << field.m_bonuses.get_bonuses()[i].getType() << "\n";
		}
		for (const auto& activeBonus: field.m_activeBonuses.get_activeBonuses())
		{
			out << "Active bonus: type=" << activeBonus.first << " active_time=" << activeBonus.second.m_activeTime << " is_active=" << activeBonus.second.isActive << "\n";
		}
		out << "Score: " << StatusBar::score << "\n"; //HERE STATUSBAR
		out << "Dimension: " << CommonResource::windowScales.width << " " << CommonResource::windowScales.height << "\n";
		out << "Difficulty: " << StatusBar::difficulty;
		out << "Playername: " << StatusBar::playerName;

		out.close();
	}

	

	static GameField* read()
	{
		/*
		std::string path{ "../save/save.json" };
		std::ifstream in;
		//GameField field{ sf::Sprite{},  sf::Sprite{} , sf::Sprite{} , 1 };
		GameField* field = new GameField{ sf::Sprite{}, sf::Sprite{}, sf::Sprite{}, 0 };
		in.open(path);
		if (!in.is_open())
		{
			std::cout << "File isn't opened!";
		}
		else
		{
			in.read((char*)field, sizeof(GameField));
		}

		in.close();
		return *field;
		*/
		std::string path{ "../save/save.json" };
		std::string object;
		std::ifstream in;
		in.open(path);
		if (!in.is_open())
		{
			std::cout << "File isn't opened!";
		}
		else
		{
			getline(in, object);
		}
		nlohmann::json j = nlohmann::json::parse(object);
		std::vector<Stand> stands;
		std::vector<Ball> balls;
		std::vector<Brick> bricks;
		std::vector<Bonus> bonuses;
		ActiveBonuses activeBonuses;
		j["balls"].get_to<std::vector<Ball>>(balls);
		j["bricks"].get_to<std::vector<Brick>>(bricks);
		j["stands"].get_to<std::vector<Stand>>(stands);
		j["bonuses"].get_to<std::vector<Bonus>>(bonuses);
		activeBonuses.from_json(j["activeBonuses"]);
		StatusBar::strings.at(0) = j["name"];
		StatusBar::additionalScore = j["additionalScore"];
		std::vector<std::string> words = getWords(j["dimension"]);
		CommonResource::windowScales = { std::atoi(words[1].c_str()), std::atoi(words[0].c_str())};
		CommonResource::difficulty = j["difficulty"];
		//for (Ball& ball : balls)
		//{
		//	ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty));
		//}
		Stands finalStands{ stands };
		Balls finalBalls{ balls };
		Bricks finalBricks{ bricks };
		if (activeBonuses.get_activeBonuses().at(Bonus::Type::DOWNBORDER).isActive)
		{
			for (Ball& ball : balls)
			{
				ball.enableBouncing();
			}
		}
		if (activeBonuses.get_activeBonuses().at(Bonus::Type::OFFCOLLISIONS).isActive)
		{
			for (Ball& ball : balls)
			{
				ball.offColisions();
			}
		}

		GameField* field = new GameField{ stands, balls, bricks, bonuses, activeBonuses };
		return field;

	}
};
