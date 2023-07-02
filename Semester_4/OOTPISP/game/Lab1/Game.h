#pragma once
#include "GameField.h"
#include "Players.h"
#include "Menu.h"

class Game
{
private:
	Players m_players;
	GameField m_gameField;
	Menu m_menu;

public:
	Game(const Players& players, const GameField& gameField, const Menu& menu);
	static void start();
	void stop();
	void loadGame();
	void saveGame();
	void pauseGame();
	static void move(std::vector<DisplaysObject*> shapes);
	static void intersects(std::vector<DisplaysObject*> shapes);
	static void draw(std::vector<DisplaysObject*> shapes, sf::RenderWindow& window);
	static void handleEventAddBonus();
	static void handleEventRemoveBonus();
	static void handleEventGameOver();
};

