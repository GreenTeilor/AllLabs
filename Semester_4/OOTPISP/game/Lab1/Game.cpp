#include "Game.h"
#include <SFML/Graphics.hpp>
#include "IntersectionEventHandler.h"
#include "EventAddBonus.h"
#include "EventBonusRemove.h"
#include "CommonResource.h"
#include "StatusBar.h"
#include <windows.h>
#include <iostream>
#include "TellPoints.h"
#include "EventGameOver.h"

Game::Game(const Players& players, const GameField& gameField, const Menu& menu) : m_players{ players }, m_gameField{ gameField }, m_menu{ menu }
{

}

void Game::start()
{
	int menuNum = 0;
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(1920, 1080), "Arkanoid!", sf::Style::Fullscreen); //, sf::Style::Fullscreen
	//app.setPosition(sf::Vector2i(1, -10));
	//app.setFramerateLimit(75);
	app.setVerticalSyncEnabled(true);
	sf::Image img;

	sf::Font mainFont;
	mainFont.loadFromFile("../fonts/Samson.ttf");
	sf::Text gameOverText("Game over!", mainFont, 60);
	gameOverText.setFillColor(sf::Color::Yellow);
	gameOverText.setPosition(800, 400);

	Menu menu{ std::vector<MenuItem>() , true }; // Подумать, как лучше создавать меню, если уже есть поле класса Game
	menu.drawMenu(app, true);
	StatusBar::initialize(); //HERE STATUSBAR
	TellPoints::initialize();

	//sf::Texture tBackground;
	//tBackground.loadFromFile("../images/background.jpg");

	//sf::Sprite sBackground(tBackground);

	//GameField* gameField{ CommonResource::field };
	IntersectionEventHandler::bricks = &CommonResource::field->m_bricks;
	IntersectionEventHandler::bonuses = &CommonResource::field->m_bonuses;
	std::vector<DisplaysObject*> shapes{ CommonResource::field->m_balls.getBalls() };
	IntersectionEventHandler::shapes = &shapes;
	for (const auto& elem : CommonResource::field->m_stands.getStands())
	{
		shapes.push_back(elem);
	}
	for (const auto& elem : CommonResource::field->m_bricks.getBricks())
	{
		shapes.push_back(elem);
	}
	for (const auto& elem : CommonResource::field->m_bonuses.getBonuses())
	{
		shapes.push_back(elem);
	}

	sf::Texture pauseButton;
	pauseButton.loadFromFile("../images/pauseButton.png");
	sf::Sprite pauseButtonSpr{ pauseButton };
	pauseButtonSpr.setPosition(10, 10);

	sf::Clock clock;
	int want_fps = 144;
	float frame_time = 1000000.0f / want_fps;
	while (app.isOpen())
	{
		float currentTime = clock.restart().asMicroseconds();

		float sleep_time = (frame_time - currentTime);
		if (sleep_time > 0)
		{
			Sleep(sleep_time / 1000);
			clock.restart();
		}

		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (e.type == sf::Event::MouseButtonReleased && menuNum == 1))
			{
				menu.setEnable();
				menu.drawMenu(app, false, shapes);
				IntersectionEventHandler::bricks = &CommonResource::field->m_bricks;
				IntersectionEventHandler::bonuses = &CommonResource::field->m_bonuses;
				CommonResource::field->m_activeBonuses.resetTimer();
				TellPoints::resetTimer();
				//StatusBar::field = &gameField;
				//shapes = std::vector<DisplaysObject*>();
				//for (const auto& elem : gameField.m_balls.getBalls())
				//{
				//	shapes.push_back(elem);
				//}
				//for (const auto& elem : gameField.m_stands.getStands())
				//{
				//	shapes.push_back(elem);
				//}
				//for (const auto& elem : gameField.m_bricks.getBricks())
				//{
				//	shapes.push_back(elem);
				//}
			}

		}
		//if (clock.getElapsedTime().asMicroseconds() > 60)
		//{
		//	time = 0;
		//	clock.restart();
		//	Sleep(0); //Makes game slower if not 0(NEED TO FIX!)
		//}

		move(shapes);
		intersects(shapes);

		int size = CommonResource::field->m_balls.size();
		shapes = std::vector<DisplaysObject*>();
		if (CommonResource::field->m_balls.getBalls()[0]->getCoordinateY() > 1080)
		{
			CommonResource::field->m_balls.removeBall(0);
		}
		for (const auto& elem : CommonResource::field->m_balls.getBalls())
		{
			shapes.push_back(elem);
		}
		for (const auto& elem : CommonResource::field->m_stands.getStands())
		{
			shapes.push_back(elem);
		}
		for (const auto& elem : CommonResource::field->m_bricks.getBricks())
		{
			shapes.push_back(elem);
		}
		for (const auto& elem : CommonResource::field->m_bonuses.getBonuses())
		{
			shapes.push_back(elem);
		}
		menuNum = 0;
		pauseButtonSpr.setColor(sf::Color::Yellow);
		if (sf::IntRect(pauseButtonSpr.getGlobalBounds().left, pauseButtonSpr.getGlobalBounds().top, pauseButtonSpr.getGlobalBounds().width, pauseButtonSpr.getGlobalBounds().height).
			contains(sf::Vector2i(app.mapPixelToCoords(sf::Mouse::getPosition(app))))) {
			pauseButtonSpr.setColor(sf::Color::Red);
			menuNum = 1;
		}

		for (int i = 0; i < shapes.size(); ++i)
			IntersectionEventHandler::screenIntersection(shapes[i]);
		CommonResource::field->m_activeBonuses.tick(CommonResource::field->m_balls);
		TellPoints::tick();

		//app.draw(sBackground);
		draw(shapes, app);

		StatusBar::update();
		StatusBar::draw(app);
		app.draw(pauseButtonSpr);
		CommonResource::field->m_activeBonuses.draw(app);
		TellPoints::draw(app);
		app.display(); //Draw window again
		app.clear();
		
		if (CommonResource::field->m_balls.size() == 0)
		{
			//app.draw(gameOverText);
			//app.display();
			//menu.drawMessageBox(app, shapes);
			menu.drawGameOver(app, shapes);
			IntersectionEventHandler::bricks = &CommonResource::field->m_bricks;
			IntersectionEventHandler::bonuses = &CommonResource::field->m_bonuses;
			for (Ball& ball : CommonResource::field->m_balls.get_balls())
			{
				ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty));
			}
			CommonResource::field->m_activeBonuses.resetTimer();
			TellPoints::resetTimer();
		}
		
	}

}

void Game::stop()
{

}

void Game::loadGame()
{

}

void Game::saveGame()
{

}

void Game::pauseGame()
{

}

void Game::move(std::vector<DisplaysObject*> shapes)
{
	for (int i = 0; i < shapes.size(); ++i)
	{
		shapes[i]->move();
	}
}

//THIS WAS ADDED IN LAST CLASS LESSON!!!
void Game::intersects(std::vector<DisplaysObject*> shapes)
{
	int bricksBreakerController = 0;
	for (int i = 0; i < shapes.size(); ++i)
	{
		if (shapes[i]->isDynamic())
		{
			for (int j = 0; j < i; ++j)
			{
				if (shapes[i]->intersects(*shapes[j]))
				{
					//ACTIONS IN CASE OF BALL COLLISION
					/*
					Ball* ball = dynamic_cast<Ball*>(shapes[i]);
					ball->setVelocityX(-ball->getVelocityX());
					ball->setVelocityY(-ball->getVelocityY());
					*/
					if (dynamic_cast<Ball*>(shapes[i]) && dynamic_cast<Brick*>(shapes[j]))
					{
						if (bricksBreakerController == 0)
						{
							++bricksBreakerController;
							IntersectionEventHandler::intersection(shapes[i], shapes[j]);
						}
						else
						{
							//goto skip;
						}
					}
					else
					{
						IntersectionEventHandler::intersection(shapes[i], shapes[j]);
					}
				}
			}

			for (int k = i + 1; k < shapes.size(); ++k)
			{
				if (shapes[i]->intersects(*shapes[k]))
				{
					//ACTIONS IN CASE OF BALL COLLISION
					/*
					Ball* ball = dynamic_cast<Ball*>(shapes[i]);
					ball->setVelocityX(-ball->getVelocityX());
					ball->setVelocityY(-ball->getVelocityY());
					*/
					if (dynamic_cast<Ball*>(shapes[i]) && dynamic_cast<Brick*>(shapes[k]))
					{
						if (bricksBreakerController == 0)
						{
							++bricksBreakerController;
							IntersectionEventHandler::intersection(shapes[i], shapes[k]);
						}
						else
						{
							//goto skip;
						}
					}
					else
					{
						IntersectionEventHandler::intersection(shapes[i], shapes[k]);
					}

				}
			}
		}
	}
}

void Game::draw(std::vector<DisplaysObject*> shapes, sf::RenderWindow& window)
{
	for (const DisplaysObject* shape : shapes)
		(*shape).draw(window);
}

void Game::handleEventAddBonus()
{
	if ((EventAddBonus::bonusesPtr != NULL) && (EventAddBonus::bricksPtr != NULL) && (EventAddBonus::index != -1))
	{
		(*EventAddBonus::bricksPtr)[EventAddBonus::index].m_bonuses[0].changeCast();
		EventAddBonus::bonusesPtr->addBonus((*EventAddBonus::bricksPtr)[EventAddBonus::index].m_bonuses[0]);
		EventAddBonus::happened = false;
		EventAddBonus::bonusesPtr = NULL;
		EventAddBonus::bricksPtr = NULL;
		EventAddBonus::index = -1;
	}
}

void Game::handleEventRemoveBonus()
{
	if ((EventBonusRemove::bonusesPtr != NULL) && (EventBonusRemove::index != -1))
	{
		if ((*EventBonusRemove::bonusesPtr)[EventBonusRemove::index].getType() == Bonus::POINTS)
			TellPoints::enable(10);
		EventBonusRemove::bonusesPtr->removeBonus(EventBonusRemove::index);
		EventBonusRemove::happened = false;
		EventBonusRemove::bonusesPtr = NULL;
		EventBonusRemove::index = -1;
	}
}

void Game::handleEventGameOver()
{
	if (EventGameOver::app != NULL)
	{
		EventGameOver::app->close();
		exit(0);
		//EventGameOver::happened = false;
		//EventGameOver::app = NULL;
	}
}
