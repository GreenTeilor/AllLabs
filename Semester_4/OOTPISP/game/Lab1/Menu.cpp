#include "Menu.h"
#include "GameField.h"
#include "CommonResource.h"
#include "Proxy.h"
#include "StatusBar.h"
#include "FormSFML.h"
#include "Game.h"
#include "EventGameOver.h"
#include "Spectator.h"

Menu::Menu(const std::vector<MenuItem>& menuItems, bool isShowMenu) : m_menuItems{ menuItems }, m_isShowMenu{ isShowMenu }
{

}

void Menu::drawMenu(sf::RenderWindow& window, bool initial, std::vector<DisplaysObject*> objects)
{
	m_menuItems.clear();

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("../images/menuBackground.jpg");
	sf::Sprite menuBackground(backgroundTexture);
	menuBackground.setPosition(0, 0);

	sf::Texture buttonTexture1;
	buttonTexture1.loadFromFile("../images/button1.png");
	sf::Sprite menu1(buttonTexture1);
	sf::Texture buttonTexture2;
	buttonTexture2.loadFromFile("../images/button1Pressed.png");

	sf::Font mainFont;
	mainFont.loadFromFile("../fonts/Samson.ttf");
	sf::Text textPlay("Play", mainFont, 60);
	textPlay.setFillColor(sf::Color::Black);
	sf::Text textLoad("Load\ngame", mainFont, 55);
	textLoad.setFillColor(sf::Color::Black);
	sf::Text textExit("Exit", mainFont, 60);
	textExit.setFillColor(sf::Color::Black);
	// Если меню вызывается во время игры, то будет такой текст
	sf::Text textSave("Save\ngame", mainFont, 55);
	textSave.setFillColor(sf::Color::Black);
	sf::Text textContinue("Continue", mainFont, 60);
	textContinue.setFillColor(sf::Color::Black);

	sf::Text textSettings("Settings", mainFont, 55);
	textSettings.setFillColor(sf::Color::Black);
	// --------------------------------------
	form::Input input(window.getSize().x/10, window.getSize().y/20, window.getSize().x / 4.8, window.getSize().y / 20);
	// --------------------------------------

	if (initial)
	{
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 300, 415), TextMessage(sf::Sprite(), 50, 300, textPlay, 370, 430)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 1080, 415), TextMessage(sf::Sprite(), 50, 300, textLoad, 1150, 410)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 1500, 415), TextMessage(sf::Sprite(), 50, 300, textExit, 1570, 430)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 700, 415), TextMessage(sf::Sprite(), 50, 300, textSettings, 715, 440)));
	}
	else
	{
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 780, 85), TextMessage(sf::Sprite(), 50, 300, textContinue, 790, 100)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 780, 685), TextMessage(sf::Sprite(), 50, 300, textSave, 850, 680)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 780, 485), TextMessage(sf::Sprite(), 50, 300, textLoad, 850, 480)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 780, 885), TextMessage(sf::Sprite(), 50, 300, textExit, 850, 905)));
		m_menuItems.push_back(MenuItem(Button(menu1, 256, 140, 780, 285), TextMessage(sf::Sprite(), 50, 300, textSettings, 798, 310)));
	}
	static sf::Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("../images/block01.png");
	t2.loadFromFile("../images/menuBackground.jpg");
	t3.loadFromFile("../images/ball1.png");
	t4.loadFromFile("../images/stand2.jpg");
	t5.loadFromFile("../images/block01.png");

	sf::Sprite sBackground(t2), sBall(t3), sStand(t4), sBlock(t1), sBonus(t5);
	GameField* gameField = new GameField{ sStand, sBall, sBlock, sBonus, 400 };

	if (initial)
	{
		CommonResource::field = gameField;
		StatusBar::field = CommonResource::field; // HERE STATUSBAR
	}

	int menuNum = 0;
	while (m_isShowMenu)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				EventGameOver::happened = true;
				EventGameOver::app = &window;
				Spectator::listenEvents();
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 1)
			{
				
				// ----------------------------------------
				std::string temp = input.readText();
				if (temp.size() != 0)
					StatusBar::strings.at(0) = temp;
				// ---------------------------------------------
				m_isShowMenu = false; //Go to game
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 2)
			{
				CommonResource::field = gameField = Serializator::read(); //Load game
				StatusBar::difficulty = CommonResource::difficulty;
				StatusBar::field = CommonResource::field; // HERE STATUSBAR
				window.setSize(sf::Vector2u(CommonResource::windowScales.width, CommonResource::windowScales.height));
				m_isShowMenu = false;
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 3)
			{
				EventGameOver::happened = true;
				EventGameOver::app = &window;
				Spectator::listenEvents(); // Exit
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 4)
			{
				Serializator::save(*CommonResource::field, StatusBar::strings.at(0)); // Save game
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 5)
			{
				drawSettings(window);
			}
			// ------------------------------------------------------------------------------------------------
			if (initial)
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						input.select(Mouse::getPosition(window), window); //поле ввода
					}
				}
				if (event.type == sf::Event::TextEntered) {
					if (input.select()) {
						input.reText(event.text.unicode);
					}
				}
			}
			// --------------------------------------------------------------------------------------------------
		}

		for (int i = 0; i < m_menuItems.size(); i++)
		{
			int x = m_menuItems.at(i).getButton().getCoordinateX();
			int y = m_menuItems.at(i).getButton().getCoordinateY();
			m_menuItems.at(i).getButton().getImage() = sf::Sprite(buttonTexture1);
			m_menuItems.at(i).getButton().getImage().setPosition(x, y);
		}

		menuNum = 0;

		if (initial)
		{
			sf::Sprite& image1 = m_menuItems.at(0).getButton().getImage();
			sf::Sprite& image2 = m_menuItems.at(1).getButton().getImage();
			sf::Sprite& image3 = m_menuItems.at(2).getButton().getImage();
			sf::Sprite& image4 = m_menuItems.at(3).getButton().getImage();
			if (sf::IntRect(image1.getGlobalBounds().left, image1.getGlobalBounds().top, image1.getGlobalBounds().width, image1.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image1.getPosition().x; int y = image1.getPosition().y; image1 = sf::Sprite(buttonTexture2); image1.setPosition(x, y); menuNum = 1;
			}
			if (sf::IntRect(image2.getGlobalBounds().left, image2.getGlobalBounds().top, image2.getGlobalBounds().width, image2.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image2.getPosition().x; int y = image2.getPosition().y; image2 = sf::Sprite(buttonTexture2); image2.setPosition(x, y); menuNum = 2;
			}
			if (sf::IntRect(image3.getGlobalBounds().left, image3.getGlobalBounds().top, image3.getGlobalBounds().width, image3.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image3.getPosition().x; int y = image3.getPosition().y; image3 = sf::Sprite(buttonTexture2); image3.setPosition(x, y); menuNum = 3;
			}
			if (sf::IntRect(image4.getGlobalBounds().left, image4.getGlobalBounds().top, image4.getGlobalBounds().width, image4.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image4.getPosition().x; int y = image4.getPosition().y; image4 = sf::Sprite(buttonTexture2); image4.setPosition(x, y); menuNum = 5;
			}
		}
		else
		{
			sf::Sprite& image1 = m_menuItems.at(0).getButton().getImage();
			sf::Sprite& image2 = m_menuItems.at(1).getButton().getImage();
			sf::Sprite& image3 = m_menuItems.at(2).getButton().getImage();
			sf::Sprite& image4 = m_menuItems.at(3).getButton().getImage();
			sf::Sprite& image5 = m_menuItems.at(4).getButton().getImage();
			if (sf::IntRect(image1.getGlobalBounds().left, image1.getGlobalBounds().top, image1.getGlobalBounds().width, image1.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image1.getPosition().x; int y = image1.getPosition().y; image1 = sf::Sprite(buttonTexture2); image1.setPosition(x, y); menuNum = 1;
			}
			if (sf::IntRect(image2.getGlobalBounds().left, image2.getGlobalBounds().top, image2.getGlobalBounds().width, image2.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image2.getPosition().x; int y = image2.getPosition().y; image2 = sf::Sprite(buttonTexture2); image2.setPosition(x, y); menuNum = 4;
			}
			if (sf::IntRect(image3.getGlobalBounds().left, image3.getGlobalBounds().top, image3.getGlobalBounds().width, image3.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image3.getPosition().x; int y = image3.getPosition().y; image3 = sf::Sprite(buttonTexture2); image3.setPosition(x, y); menuNum = 2;
			}
			if (sf::IntRect(image4.getGlobalBounds().left, image4.getGlobalBounds().top, image4.getGlobalBounds().width, image4.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image4.getPosition().x; int y = image4.getPosition().y; image4 = sf::Sprite(buttonTexture2); image4.setPosition(x, y); menuNum = 3;
			}
			if (sf::IntRect(image5.getGlobalBounds().left, image5.getGlobalBounds().top, image5.getGlobalBounds().width, image5.getGlobalBounds().height).
				contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
				int x = image5.getPosition().x; int y = image5.getPosition().y; image5 = sf::Sprite(buttonTexture2); image5.setPosition(x, y); menuNum = 5;
			}
		}

		window.clear();
		
		// ------------------------------------
		if (initial)
		{
			//window.draw(menuBackground);
			//
			std::vector<DisplaysObject*> shapes{ CommonResource::field->m_balls.getBalls() };
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
			//Game::draw(shapes, window);
			window.draw(sBackground);
			window.draw(input.displayButton());
			window.draw(input.displayBOX());
			window.draw(input.displayText());
		} 
		else
		{
			Game::draw(objects, window);
		}
		// ------------------------------------
		for (int i = 0; i < m_menuItems.size(); i++)
		{
			window.draw(m_menuItems.at(i).getButton().getImage());
			window.draw(m_menuItems.at(i).getMessage().getText());
		}
		window.display();

	}
}

void Menu::drawSettings(sf::RenderWindow& window)
{
	window.clear();
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("../images/menuBackground.jpg");
	sf::Texture rButton1Texture;
	rButton1Texture.loadFromFile("../images/rButton1.png");
	sf::Texture rButton2Texture;
	rButton2Texture.loadFromFile("../images/rButton2.png");
	sf::Texture buttonTexture1;
	buttonTexture1.loadFromFile("../images/button1.png");
	sf::Texture buttonTexture2;
	buttonTexture2.loadFromFile("../images/button1Pressed.png");

	sf::Sprite menuBackground(backgroundTexture);
	menuBackground.setPosition(0, 0);
	sf::Sprite rButton1Sprite(rButton2Texture);
	sf::Sprite rButton2Sprite(rButton2Texture);
	sf::Sprite rButton3Sprite(rButton2Texture);
	sf::Sprite rButton4Sprite(rButton2Texture);
	sf::Sprite rButton5Sprite(rButton1Texture);

	sf::Sprite rButton6Sprite(rButton2Texture);
	sf::Sprite rButton7Sprite(rButton2Texture);
	sf::Sprite rButton8Sprite(rButton2Texture);
	sf::Sprite rButton9Sprite(rButton2Texture);
	sf::Sprite rButton10Sprite(rButton1Texture);

	if (window.getSize() == sf::Vector2u(1067, 600))
	{
		rButton1Sprite.setTexture(rButton1Texture);
		rButton2Sprite.setTexture(rButton2Texture);
		rButton3Sprite.setTexture(rButton2Texture);
		rButton4Sprite.setTexture(rButton2Texture);
		rButton5Sprite.setTexture(rButton2Texture);
	}
	else if (window.getSize() == sf::Vector2u(1280, 720))
	{
		rButton1Sprite.setTexture(rButton2Texture);
		rButton2Sprite.setTexture(rButton1Texture);
		rButton3Sprite.setTexture(rButton2Texture);
		rButton4Sprite.setTexture(rButton2Texture);
		rButton5Sprite.setTexture(rButton2Texture);
	} else if (window.getSize() == sf::Vector2u(1360, 768))
	{
		rButton1Sprite.setTexture(rButton2Texture);
		rButton2Sprite.setTexture(rButton2Texture);
		rButton3Sprite.setTexture(rButton1Texture);
		rButton4Sprite.setTexture(rButton2Texture);
		rButton5Sprite.setTexture(rButton2Texture);
	} else if (window.getSize() == sf::Vector2u(1600, 900))
	{
		rButton1Sprite.setTexture(rButton2Texture);
		rButton2Sprite.setTexture(rButton2Texture);
		rButton3Sprite.setTexture(rButton2Texture);
		rButton4Sprite.setTexture(rButton1Texture);
		rButton5Sprite.setTexture(rButton2Texture);
	} else
	{
		rButton1Sprite.setTexture(rButton2Texture);
		rButton2Sprite.setTexture(rButton2Texture);
		rButton3Sprite.setTexture(rButton2Texture);
		rButton4Sprite.setTexture(rButton2Texture);
		rButton5Sprite.setTexture(rButton1Texture);
	}

	if (CommonResource::difficulty == "easy")
	{
		rButton6Sprite.setTexture(rButton1Texture);
		rButton7Sprite.setTexture(rButton2Texture);
		rButton8Sprite.setTexture(rButton2Texture);
		rButton9Sprite.setTexture(rButton2Texture);
		rButton10Sprite.setTexture(rButton2Texture);
	}
	else if (CommonResource::difficulty == "medium")
	{
		rButton6Sprite.setTexture(rButton2Texture);
		rButton7Sprite.setTexture(rButton1Texture);
		rButton8Sprite.setTexture(rButton2Texture);
		rButton9Sprite.setTexture(rButton2Texture);
		rButton10Sprite.setTexture(rButton2Texture);
	}
	else if (CommonResource::difficulty == "hard")
	{
		rButton6Sprite.setTexture(rButton2Texture);
		rButton7Sprite.setTexture(rButton2Texture);
		rButton8Sprite.setTexture(rButton1Texture);
		rButton9Sprite.setTexture(rButton2Texture);
		rButton10Sprite.setTexture(rButton2Texture);
	}
	else if (CommonResource::difficulty == "insane")
	{
		rButton6Sprite.setTexture(rButton2Texture);
		rButton7Sprite.setTexture(rButton2Texture);
		rButton8Sprite.setTexture(rButton2Texture);
		rButton9Sprite.setTexture(rButton1Texture);
		rButton10Sprite.setTexture(rButton2Texture);
	}
	else
	{
		rButton6Sprite.setTexture(rButton2Texture);
		rButton7Sprite.setTexture(rButton2Texture);
		rButton8Sprite.setTexture(rButton2Texture);
		rButton9Sprite.setTexture(rButton2Texture);
		rButton10Sprite.setTexture(rButton1Texture);
	}

	rButton1Sprite.setPosition(200, 200);
	rButton2Sprite.setPosition(450, 200);
	rButton3Sprite.setPosition(700, 200);
	rButton4Sprite.setPosition(950, 200);
	rButton5Sprite.setPosition(1200, 200);
	rButton6Sprite.setPosition(200, 400);
	rButton7Sprite.setPosition(450, 400);
	rButton8Sprite.setPosition(700, 400);
	rButton9Sprite.setPosition(950, 400);
	rButton10Sprite.setPosition(1200, 400);

	sf::Sprite menu1(buttonTexture1);
	menu1.setPosition(800, 600);

	sf::Font mainFont;
	mainFont.loadFromFile("../fonts/Samson.ttf");
	sf::Text textResolution1067_600("1067x600", mainFont, 60);
	textResolution1067_600.setFillColor(sf::Color::Yellow);
	sf::Text textResolution1280_720("1280x720", mainFont, 60);
	textResolution1280_720.setFillColor(sf::Color::Yellow);
	sf::Text textResolution1360_768("1368x768", mainFont, 60);
	textResolution1360_768.setFillColor(sf::Color::Yellow);
	sf::Text textResolution1600_900("1600x900", mainFont, 60);
	textResolution1600_900.setFillColor(sf::Color::Yellow);
	sf::Text textResolution1920_1080("1920x1080", mainFont, 60);
	textResolution1920_1080.setFillColor(sf::Color::Yellow);

	sf::Text textDifficultyEasy("easy", mainFont, 60);
	textDifficultyEasy.setFillColor(sf::Color::Yellow);
	sf::Text textDifficultyMedium("medium", mainFont, 60);
	textDifficultyMedium.setFillColor(sf::Color::Yellow);
	sf::Text textDifficultyHard("hard", mainFont, 60);
	textDifficultyHard.setFillColor(sf::Color::Yellow);
	sf::Text textDifficultyInsane("insane", mainFont, 60);
	textDifficultyInsane.setFillColor(sf::Color::Yellow);
	sf::Text textDifficultyGod("god", mainFont, 60);
	textDifficultyGod.setFillColor(sf::Color::Yellow);

	sf::Text textExit("Exit", mainFont, 60);
	textExit.setFillColor(sf::Color::Black);
	textExit.setPosition(870, 620);
	textResolution1067_600.setPosition(100, 100);
	textResolution1280_720.setPosition(350, 100);
	textResolution1360_768.setPosition(600, 100);
	textResolution1600_900.setPosition(850, 100);
	textResolution1920_1080.setPosition(1100, 100);

	textDifficultyEasy.setPosition(100, 300);
	textDifficultyMedium.setPosition(350, 300);
	textDifficultyHard.setPosition(600, 300);
	textDifficultyInsane.setPosition(850, 300);
	textDifficultyGod.setPosition(1100, 300);
	

	int menuNum = 0;
	bool isShowSettings = true;
	while (isShowSettings)
	{
		menu1.setTexture(buttonTexture1);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				EventGameOver::happened = true;
				EventGameOver::app = &window;
				Spectator::listenEvents();
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 11)
			{
				isShowSettings = false;
			}
		}
		menuNum = 0;
		if (IntRect(rButton1Sprite.getGlobalBounds().left, rButton1Sprite.getGlobalBounds().top, rButton1Sprite.getGlobalBounds().width, rButton1Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 1;
		}
		if (IntRect(rButton2Sprite.getGlobalBounds().left, rButton2Sprite.getGlobalBounds().top, rButton2Sprite.getGlobalBounds().width, rButton2Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 2;
		}
		if (IntRect(rButton3Sprite.getGlobalBounds().left, rButton3Sprite.getGlobalBounds().top, rButton3Sprite.getGlobalBounds().width, rButton3Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 3;
		}
		if (IntRect(rButton4Sprite.getGlobalBounds().left, rButton4Sprite.getGlobalBounds().top, rButton4Sprite.getGlobalBounds().width, rButton4Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 4;
		}
		if (IntRect(rButton5Sprite.getGlobalBounds().left, rButton5Sprite.getGlobalBounds().top, rButton5Sprite.getGlobalBounds().width, rButton5Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 5;
		}
		if (IntRect(rButton6Sprite.getGlobalBounds().left, rButton6Sprite.getGlobalBounds().top, rButton6Sprite.getGlobalBounds().width, rButton6Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 6;
		}
		if (IntRect(rButton7Sprite.getGlobalBounds().left, rButton7Sprite.getGlobalBounds().top, rButton7Sprite.getGlobalBounds().width, rButton7Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 7;
		}
		if (IntRect(rButton8Sprite.getGlobalBounds().left, rButton8Sprite.getGlobalBounds().top, rButton8Sprite.getGlobalBounds().width, rButton8Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 8;
		}
		if (IntRect(rButton9Sprite.getGlobalBounds().left, rButton9Sprite.getGlobalBounds().top, rButton9Sprite.getGlobalBounds().width, rButton9Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 9;
		}
		if (IntRect(rButton10Sprite.getGlobalBounds().left, rButton10Sprite.getGlobalBounds().top, rButton10Sprite.getGlobalBounds().width, rButton10Sprite.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menuNum = 10;
		}
		if (IntRect(menu1.getGlobalBounds().left, menu1.getGlobalBounds().top, menu1.getGlobalBounds().width, menu1.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			menu1.setTexture(buttonTexture2);
			menuNum = 11;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
		if (menuNum != 6)
			if (menuNum == 1)
			{
				rButton1Sprite.setTexture(rButton1Texture);
				rButton2Sprite.setTexture(rButton2Texture);
				rButton3Sprite.setTexture(rButton2Texture);
				rButton4Sprite.setTexture(rButton2Texture);
				rButton5Sprite.setTexture(rButton2Texture);
				window.setSize(sf::Vector2u(1067, 600));
				window.setPosition(sf::Vector2i(0, 0));
				CommonResource::windowScales.width = window.getSize().x;
				CommonResource::windowScales.height = window.getSize().y;
			}
			if (menuNum == 2)
			{
				rButton1Sprite.setTexture(rButton2Texture);
				rButton2Sprite.setTexture(rButton1Texture);
				rButton3Sprite.setTexture(rButton2Texture);
				rButton4Sprite.setTexture(rButton2Texture);
				rButton5Sprite.setTexture(rButton2Texture);
				window.setSize(sf::Vector2u(1280, 720));
				CommonResource::windowScales.width = window.getSize().x;
				CommonResource::windowScales.height = window.getSize().y;
			}
			if (menuNum == 3)
			{
				rButton1Sprite.setTexture(rButton2Texture);
				rButton2Sprite.setTexture(rButton2Texture);
				rButton3Sprite.setTexture(rButton1Texture);
				rButton4Sprite.setTexture(rButton2Texture);
				rButton5Sprite.setTexture(rButton2Texture);
				window.setSize(sf::Vector2u(1360, 768));
				CommonResource::windowScales.width = window.getSize().x;
				CommonResource::windowScales.height = window.getSize().y;
			}
			if (menuNum == 4)
			{
				rButton1Sprite.setTexture(rButton2Texture);
				rButton2Sprite.setTexture(rButton2Texture);
				rButton3Sprite.setTexture(rButton2Texture);
				rButton4Sprite.setTexture(rButton1Texture);
				rButton5Sprite.setTexture(rButton2Texture);
				window.setSize(sf::Vector2u(1600, 900));
				CommonResource::windowScales.width = window.getSize().x;
				CommonResource::windowScales.height = window.getSize().y;
			}
			if (menuNum == 5)
			{
				rButton1Sprite.setTexture(rButton2Texture);
				rButton2Sprite.setTexture(rButton2Texture);
				rButton3Sprite.setTexture(rButton2Texture);
				rButton4Sprite.setTexture(rButton2Texture);
				rButton5Sprite.setTexture(rButton1Texture);
				window.setSize(sf::Vector2u(1920, 1080));
				CommonResource::windowScales.width = window.getSize().x;
				CommonResource::windowScales.height = window.getSize().y;
			}
			if (menuNum == 6)
			{
				rButton6Sprite.setTexture(rButton1Texture);
				rButton7Sprite.setTexture(rButton2Texture);
				rButton8Sprite.setTexture(rButton2Texture);
				rButton9Sprite.setTexture(rButton2Texture);
				rButton10Sprite.setTexture(rButton2Texture);
				StatusBar::difficulty = CommonResource::difficulty = "easy";
				StatusBar::ballSpeed = CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty);
				for (Ball& ball : CommonResource::field->m_balls.get_balls()) 
				{
					ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty) * abs(ball.getVelocityY()) / ball.getVelocityY());
				}
			}
			if (menuNum == 7)
			{
				rButton6Sprite.setTexture(rButton2Texture);
				rButton7Sprite.setTexture(rButton1Texture);
				rButton8Sprite.setTexture(rButton2Texture);
				rButton9Sprite.setTexture(rButton2Texture);
				rButton10Sprite.setTexture(rButton2Texture);
				StatusBar::difficulty = CommonResource::difficulty = "medium";
				StatusBar::ballSpeed = CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty);
				for (Ball& ball : CommonResource::field->m_balls.get_balls())
				{
					ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty) * abs(ball.getVelocityY()) / ball.getVelocityY());
				}
			}
			if (menuNum == 8)
			{
				rButton6Sprite.setTexture(rButton2Texture);
				rButton7Sprite.setTexture(rButton2Texture);
				rButton8Sprite.setTexture(rButton1Texture);
				rButton9Sprite.setTexture(rButton2Texture);
				rButton10Sprite.setTexture(rButton2Texture);
				StatusBar::difficulty = CommonResource::difficulty = "hard";
				StatusBar::ballSpeed = CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty);
				for (Ball& ball : CommonResource::field->m_balls.get_balls())
				{
					ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty) * abs(ball.getVelocityY()) / ball.getVelocityY());
				}
			}
			if (menuNum == 9)
			{
				rButton6Sprite.setTexture(rButton2Texture);
				rButton7Sprite.setTexture(rButton2Texture);
				rButton8Sprite.setTexture(rButton2Texture);
				rButton9Sprite.setTexture(rButton1Texture);
				rButton10Sprite.setTexture(rButton2Texture);
				StatusBar::difficulty = CommonResource::difficulty = "insane";
				StatusBar::ballSpeed = CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty);
				for (Ball& ball : CommonResource::field->m_balls.get_balls())
				{
					ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty) * abs(ball.getVelocityY()) / ball.getVelocityY());
				}
			}
			if (menuNum == 10)
			{
				rButton6Sprite.setTexture(rButton2Texture);
				rButton7Sprite.setTexture(rButton2Texture);
				rButton8Sprite.setTexture(rButton2Texture);
				rButton9Sprite.setTexture(rButton2Texture);
				rButton10Sprite.setTexture(rButton1Texture);
				StatusBar::difficulty = CommonResource::difficulty = "god";
				StatusBar::ballSpeed = CommonResource::getBallVelocityByDifficulty(StatusBar::difficulty);
				for (Ball& ball : CommonResource::field->m_balls.get_balls())
				{
					ball.setVelocityY(CommonResource::getBallVelocityByDifficulty(CommonResource::difficulty) * abs(ball.getVelocityY()) / ball.getVelocityY());
				}
			}
		}

		window.clear();
		window.draw(menuBackground);
		window.draw(rButton1Sprite);
		window.draw(rButton2Sprite);
		window.draw(rButton3Sprite);
		window.draw(rButton4Sprite);
		window.draw(rButton5Sprite);
		window.draw(rButton6Sprite);
		window.draw(rButton7Sprite);
		window.draw(rButton8Sprite);
		window.draw(rButton9Sprite);
		window.draw(rButton10Sprite);
		window.draw(menu1);
		window.draw(textExit);
		window.draw(textResolution1067_600);
		window.draw(textResolution1280_720);
		window.draw(textResolution1360_768);
		window.draw(textResolution1600_900);
		window.draw(textResolution1920_1080);
		window.draw(textDifficultyEasy);
		window.draw(textDifficultyMedium);
		window.draw(textDifficultyHard);
		window.draw(textDifficultyInsane);
		window.draw(textDifficultyGod);
		
		window.display();
	}

}

void Menu::drawGameOver(sf::RenderWindow& window, std::vector<DisplaysObject*> objects)
{
	static sf::Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("../images/block01.png");
	t2.loadFromFile("../images/menuBackground.jpg");
	t3.loadFromFile("../images/ball1.png");
	t4.loadFromFile("../images/stand2.jpg");
	t5.loadFromFile("../images/block01.png");

	sf::Sprite sBackground(t2), sBall(t3), sStand(t4), sBlock(t1), sBonus(t5);
	sBackground.setPosition(0, 0);
	sf::Texture buttonTexture1;
	buttonTexture1.loadFromFile("../images/button1.png");
	sf::Texture buttonTexture2;
	buttonTexture2.loadFromFile("../images/button1Pressed.png");
	sf::Font mainFont;
	mainFont.loadFromFile("../fonts/Samson.ttf");
	sf::Text textGameOver("Game over", mainFont, 60);
	textGameOver.setOutlineThickness(2);
	textGameOver.setOutlineColor(sf::Color::Yellow);
	textGameOver.setFillColor(sf::Color::Black);
	textGameOver.setStyle(sf::Text::Bold);
	sf::Text textAgain("Play again", mainFont, 50);
	textAgain.setFillColor(sf::Color::Black);
	sf::Text textMainMenu("Main menu", mainFont, 50);
	textMainMenu.setFillColor(sf::Color::Black);
	sf::Sprite buttonAgain(buttonTexture1);
	sf::Sprite buttonMainMenu(buttonTexture2);
	
	textGameOver.setPosition(750, 200);
	textAgain.setPosition(770, 420);
	textMainMenu.setPosition(770, 620);
	buttonAgain.setPosition(750, 400);
	buttonMainMenu.setPosition(750, 600);
	int menuNum = 0;
	bool isShowMenu = true;
	while (isShowMenu)
	{
		buttonAgain.setTexture(buttonTexture1);
		buttonMainMenu.setTexture(buttonTexture1);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				EventGameOver::happened = true;
				EventGameOver::app = &window;
				Spectator::listenEvents();
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 1)
			{
				GameField* gameField = new GameField{ sStand, sBall, sBlock, sBonus, 400 };
				CommonResource::field = gameField;
				StatusBar::field = CommonResource::field;
				isShowMenu = false;
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 2)
			{
				this->setEnable();
				drawMenu(window, true);
				isShowMenu = false;
			}
		}

		int x = buttonAgain.getPosition().x;
		int y = buttonAgain.getPosition().y;
		buttonAgain = sf::Sprite(buttonTexture1);
		buttonAgain.setPosition(x, y);

		x = buttonMainMenu.getPosition().x;
		y = buttonMainMenu.getPosition().y;
		buttonMainMenu = sf::Sprite(buttonTexture1);
		buttonMainMenu.setPosition(x, y);


		menuNum = 0;
		if (IntRect(buttonAgain.getGlobalBounds().left, buttonAgain.getGlobalBounds().top, buttonAgain.getGlobalBounds().width, buttonAgain.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			x = buttonAgain.getPosition().x; int y = buttonAgain.getPosition().y; buttonAgain = sf::Sprite(buttonTexture2); buttonAgain.setPosition(x, y); menuNum = 1;
			//buttonAgain.setTexture(buttonTexture2); menuNum = 1;
		}
		if (IntRect(buttonMainMenu.getGlobalBounds().left, buttonMainMenu.getGlobalBounds().top, buttonMainMenu.getGlobalBounds().width, buttonMainMenu.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			x = buttonMainMenu.getPosition().x; int y = buttonMainMenu.getPosition().y; buttonMainMenu = sf::Sprite(buttonTexture2); buttonMainMenu.setPosition(x, y); menuNum = 2;
			//buttonMainMenu.setTexture(buttonTexture2); menuNum = 2;
		}

		Game::draw(objects, window);
		StatusBar::draw(window);
		window.draw(buttonAgain);
		window.draw(buttonMainMenu);
		window.draw(textGameOver);
		window.draw(textAgain);
		window.draw(textMainMenu);
		window.display();
		window.clear();
	}
}

void Menu::drawMessageBox(sf::RenderWindow& window, std::vector<DisplaysObject*> objects)
{
	static sf::Texture t1, t2, t3, t4, t5;
	//sf::RectangleShape back;
	//back.setPosition(400, 400);
	//back.setFillColor(sf::Color::Yellow);
	//back.setScale(200, 200);
	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
	rectangle.setScale(7, 3);
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(550, 180);
	t1.loadFromFile("../images/block01.png");
	t2.loadFromFile("../images/menuBackground.jpg");
	t3.loadFromFile("../images/ball1.png");
	t4.loadFromFile("../images/stand2.jpg");
	t5.loadFromFile("../images/block01.png");
	//back.setTexture(&t1);

	sf::Sprite sBackground(t2), sBall(t3), sStand(t4), sBlock(t1), sBonus(t5);
	sBackground.setPosition(0, 0);
	sf::Texture buttonTexture1;
	buttonTexture1.loadFromFile("../images/button1.png");
	sf::Texture buttonTexture2;
	buttonTexture2.loadFromFile("../images/button1Pressed.png");
	sf::Font mainFont;
	mainFont.loadFromFile("../fonts/Samson.ttf");
	sf::Text textGameOver("Game over", mainFont, 60);
	textGameOver.setOutlineThickness(2);
	textGameOver.setOutlineColor(sf::Color::Yellow);
	textGameOver.setFillColor(sf::Color::Black);
	textGameOver.setStyle(sf::Text::Bold);
	sf::Text textAgain("Ok", mainFont, 50);
	textAgain.setFillColor(sf::Color::Black);
	sf::Sprite buttonAgain(buttonTexture1);

	textGameOver.setPosition(750, 200);
	textAgain.setPosition(850, 420);
	buttonAgain.setPosition(750, 400);
	int menuNum = 0;
	bool isShowMenu = true;
	while (isShowMenu)
	{
		buttonAgain.setTexture(buttonTexture1);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				EventGameOver::happened = true;
				EventGameOver::app = &window;
				Spectator::listenEvents();
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 1)
			{
				GameField* gameField = new GameField{ sStand, sBall, sBlock, sBonus, 400 };
				CommonResource::field = gameField;
				StatusBar::field = CommonResource::field;
				isShowMenu = false;
			}
			if (event.type == sf::Event::MouseButtonReleased && menuNum == 2)
			{
				this->setEnable();
				drawMenu(window, true);
				isShowMenu = false;
			}
		}

		int x = buttonAgain.getPosition().x;
		int y = buttonAgain.getPosition().y;
		buttonAgain = sf::Sprite(buttonTexture1);
		buttonAgain.setPosition(x, y);

		menuNum = 0;
		if (IntRect(buttonAgain.getGlobalBounds().left, buttonAgain.getGlobalBounds().top, buttonAgain.getGlobalBounds().width, buttonAgain.getGlobalBounds().height).
			contains(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
		{
			x = buttonAgain.getPosition().x; int y = buttonAgain.getPosition().y; buttonAgain = sf::Sprite(buttonTexture2); buttonAgain.setPosition(x, y); menuNum = 1;
			//buttonAgain.setTexture(buttonTexture2); menuNum = 1;
		}

		Game::draw(objects, window);
		StatusBar::draw(window);
		//window.draw(back);
		window.draw(rectangle);
		window.draw(buttonAgain);
		window.draw(textGameOver);
		window.draw(textAgain);
		window.display();
		window.clear();
	}
}

void Menu::initialize() const
{

}

void Menu::setEnable()
{
	m_isShowMenu = true;
}