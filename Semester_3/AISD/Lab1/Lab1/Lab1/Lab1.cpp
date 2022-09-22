#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>

using namespace sf;

void setSpriteSize(Sprite& sprite, const float width, const float height)
{
	sf::Vector2f targetSize(width, height); //Size in pixels
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
}

enum GameState
{
	GAME_START_COLOR_CHOICE,
	GAME_START_STUFF_CHOICE,
	MAIN,
	ELEVATOR_MENU
};

static GameState gameState{ GAME_START_COLOR_CHOICE };

class Floor
{
public:
	struct Staircase
	{
		Sprite staircaseImage;
		int nextFloor;
	};

private:
	Sprite m_floorColor;
	Sprite m_wall;
	Staircase m_staircase;
	Sprite m_elevator;
	Sprite m_exit;
	Sprite m_pointer;
	Sprite m_specialStuff1;
	Sprite m_specialStuff2;

public:
	//Represemt gaming field where 0 - empty 1 - wall 2 - staircase 3 - elevator 4 - exit 5 - pointer to exit 6 - special stuff1 7 - special stuff2
	int m_map[16][16];
	Floor(const Texture& floorColor, const Texture& wall, const Texture& elevator, const Texture& staircaseImage, const int staircaseNextLevel, const Texture& exit, const Texture& pointer, const Texture& specialStuff1, const Texture& specialStuff2, const int(*map)[16])
	{
		m_floorColor.setTexture(floorColor);
		m_floorColor.setPosition(0.0f, 0.0f);
		setSpriteSize(m_floorColor, 800.0f, 800.0f);

		m_wall.setTexture(wall);
		m_wall.setPosition(0.0f, 0.0f);
		setSpriteSize(m_wall, 50.0f, 50.0f);

		m_elevator.setTexture(elevator);
		m_elevator.setPosition(0.0f, 0.0f);
		setSpriteSize(m_elevator, 50.0f, 50.0f);

		m_staircase.staircaseImage.setTexture(staircaseImage);
		m_staircase.staircaseImage.setPosition(0.0f, 0.0f);
		setSpriteSize(m_staircase.staircaseImage, 50.0f, 50.0f);
		m_staircase.nextFloor = staircaseNextLevel;

		m_exit.setTexture(exit);
		m_exit.setPosition(0.0f, 0.0f);
		setSpriteSize(m_exit, 50.0f, 50.0f);

		m_pointer.setTexture(pointer);
		m_pointer.setPosition(0.0f, 0.0f);
		setSpriteSize(m_pointer, 50.0f, 50.0f);

		m_specialStuff1.setTexture(specialStuff1);
		m_specialStuff1.setPosition(0.0f, 0.0f);
		setSpriteSize(m_specialStuff1, 50.0f, 50.0f);

		m_specialStuff2.setTexture(specialStuff2);
		m_specialStuff2.setPosition(0.0f, 0.0f);
		setSpriteSize(m_specialStuff2, 50.0f, 50.0f);

		for (int i = 0; i < 16; ++i)
			for (int j = 0; j < 16; ++j)
				m_map[i][j] = map[i][j];
	}

	Floor()
	{

	}

	void draw(RenderWindow& window)
	{
		window.draw(m_floorColor);
		Sprite mapElement;
		mapElement.setPosition(50.0f, 50.0f);
		for (int i = 0; i < 16; ++i)
			for (int j = 0; j < 16; ++j)
			{
				switch (m_map[i][j])
				{
				case 0:
					;
					break;
				case 1:
					mapElement = m_wall;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 2:
					mapElement = m_staircase.staircaseImage;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 3:
					mapElement = m_elevator;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 4:
					mapElement = m_exit;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 5:
					mapElement = m_pointer;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 6:
					mapElement = m_specialStuff1;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				case 7:
					mapElement = m_specialStuff2;
					mapElement.setPosition(j * 50.0f, i * 50.0f);
					window.draw(mapElement);
					break;
				}
			}
	}

};

class Player
{
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

	struct Coordinates
	{
		int x;
		int y;
	};

private:
	Sprite m_playerImage;
	Coordinates m_coordinates;
	int m_currentFloor;

	bool isCollision(const int(*map)[16])
	{
		if (m_coordinates.x < 0 || m_coordinates.x > 15 || m_coordinates.y < 0 || m_coordinates.y > 15 || (map[m_coordinates.x][m_coordinates.y] == 1))
			return true;
		return false;
	}

public:
	Player(const Texture& playerImage, Coordinates coordinates = { 0, 0 }, int currentFloor = 2) : m_coordinates{ coordinates }, m_currentFloor{ currentFloor }
	{
		m_playerImage.setTexture(playerImage);
		m_playerImage.setPosition(50.0f*coordinates.x, 50.0f*coordinates.y);
		setSpriteSize(m_playerImage, 50.0f, 50.0f);
	}
	Player()
	{

	}

	void move(RenderWindow& window, const int(*map)[16], Direction direction)
	{
		Coordinates previousCoordinates{ m_coordinates };
		switch (direction)
		{
		case LEFT:
			m_coordinates.y -= 1;
			break;
		case RIGHT:
			m_coordinates.y += 1;
			break;
		case UP:
			m_coordinates.x -= 1;
			break;
		case DOWN:
			m_coordinates.x += 1;
			break;
		case NONE:
			;
			break;
		}
		m_playerImage.setPosition(m_coordinates.y * 50.0f, m_coordinates.x * 50.0f);
		if (isCollision(map))
			m_coordinates = previousCoordinates;
		if (map[m_coordinates.x][m_coordinates.y] == 2)
			--m_currentFloor;
		if (map[m_coordinates.x][m_coordinates.y] == 3)
		{
			gameState = ELEVATOR_MENU;
			if (m_coordinates.x == 0 && m_coordinates.y == 15) --m_coordinates.y;
			else ++m_coordinates.y;
		}
			
		window.draw(m_playerImage);
	}

	int getCurrentFloor()
	{
		return m_currentFloor;
	}

	void setCurrentFloor(const int floor)
	{
		m_currentFloor = floor;
	}

	Coordinates getCoordinates()
	{
		return m_coordinates;
	}

	void setCoordinates(const Coordinates& coordinates)
	{
		m_coordinates = coordinates;
	}

};



void createMap1(int (*map1)[16])
{
	map1[3][0] = 2;
	map1[0][15] = 3;
	map1[15][0] = 3;
	map1[15][15] = 2;
	map1[8][9] = 6;
	map1[13][3] = 7;
	for (int i = 5; i < 11; ++i)
		map1[5][i] = 1;
	for (int i = 1; i < 11; ++i)
		map1[3][i] = 1;
	for (int i = 5; i < 15; ++i)
		map1[i][4] = 1;
	for (int i = 1; i < 9; ++i)
		map1[i][12] = 1;
	for (int i = 12; i > 5; --i)
		map1[9][i] = 1;
	for (int i = 0; i < 5; ++i)
		map1[14][i] = 1;
	for (int i = 1; i < 5; ++i)
		map1[10][i] = 1;
	for (int i = 0; i < 4; ++i)
		map1[i][1] = 1;
	for (int i = 0; i < 3; ++i)
		map1[8][i] = 1;
	for (int i = 1; i < 4; ++i)
		map1[6][i] = 1;
	for (int i = 6; i < 9; ++i)
		map1[i][10] = 1;
	for (int i = 10; i < 15; ++i)
		map1[i][11] = 1;
	for (int i = 12; i < 16; ++i)
		map1[14][i] = 1;
}

void createMap2(int(*map1)[16])
{
	map1[6][0] = 2;
	map1[0][15] = 3;
	map1[15][0] = 3;
	map1[7][14] = 2;
	map1[8][9] = 6;
	map1[13][3] = 7;
	for (int i = 0; i < 14; ++i)
		map1[1][i] = 1;
	for (int i = 2; i < 7; ++i)
		map1[i][13] = 1;
	for (int i = 12; i > 7; --i)
		map1[6][i] = 1;
	for (int i = 5; i > 2; --i)
		map1[i][8] = 1;
	for (int i = 3; i < 15; ++i)
		map1[i][8] = 1;
	for (int i = 0; i < 7; ++i)
		map1[14][i] = 1;
	for (int i = 13; i > 7; --i)
		map1[i][6] = 1;
	for (int i = 1; i < 7; ++i)
		map1[8][i] = 1;
	for (int i = 9; i < 15; ++i)
		map1[11][i] = 1;
	for (int i = 12; i < 16; ++i)
		map1[i][14] = 1;
}

void createMap3(int(*map1)[16])
{
	map1[0][15] = 3;
	map1[15][0] = 3;
	map1[6][7] = 6;
	map1[13][5] = 7;
	map1[15][15] = 4;
	for (int i = 8; i < 16; ++i)
		map1[i][14] = 1;
	for (int i = 0; i < 7; ++i)
		map1[14][i] = 1;
	for (int i = 13; i > 1; --i)
		map1[i][6] = 1;
	for (int i = 6; i < 14; ++i)
			map1[1][i] = 1;
	for (int i = 7; i < 11; ++i)
		map1[7][i] = 1;
	for (int i = 0; i < 5; ++i)
		map1[9][i] = 1;
	for (int i = 7; i > 2; --i)
		map1[i][11] = 1;
	for (int i = 5; i > 0; --i)
		map1[4][i] = 1;
	for (int i = 8; i < 12; ++i)
		map1[i][10] = 1;
	for (int i = 13; i > 8; --i)
		map1[14][i] = 1;
}


//
// THIS TRIES TO SEARCH PATH, MORE LIKELY DOESN'T WORK
//


//Copied from python
void make_step(int(*m)[16], int(*a)[16], int k)
{
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			if (m[i][j] == k)
			{
				if (i > 0 && m[i - 1][j] == 0 && a[i - 1][j] == 0) m[i - 1][j] = k + 1;
				if (j > 0 && m[i][j - 1] == 0 && a[i][j - 1] == 0) m[i][j - 1] = k + 1;
				if (i < 16 && m[i + 1][j] == 0 && a[i + 1][j] == 0) m[i + 1][j] = k + 1;
				if (j < 15 && m[i][j + 1] == 0 && a[i][j + 1] == 0) m[i][j + 1] = k + 1;
			}
}

//Build path in labyrinth
std::vector<Player::Coordinates> findPath(int(*map)[16], const Player::Coordinates& start, const Player::Coordinates exit1, const Player::Coordinates exit2)
{
	//Create array only with 0 and 1 to represent it like labyrinth
	int a[16][16];
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			if (map[i][j] != 0 && map[i][j] != 2 && map[i][j] != 4 && map[i][j] != 5)
				a[i][j] = 1;
			else
				a[i][j] = 0;
	int m[16][16]{};
	m[start.x][start.y] = 1;
	int k = 0;
	while (m[exit1.x][exit1.y] == 0 && m[exit2.x][exit2.y] == 0)
	{
		k += 1;
		make_step(m, a, k);
	}

	std::vector<Player::Coordinates> the_path;

	int i, j;
	if (m[exit1.x][exit1.y] != 0)
	{
		i = exit1.x;
		j = exit1.y;
	}
	else
	{
		i = exit2.x;
		j = exit2.y;
	}

	k = m[i][j];
	while (k > 2)
	{
		if (i > 0 && m[i - 1][j] == k - 1)
		{
			i = i - 1;

			the_path.push_back({ i, j });
			k -= 1;
		}
		else if (j > 0 && m[i][j - 1] == k - 1)
		{
			j = j - 1;
			the_path.push_back({ i, j });
			k -= 1;
		}
		else if (i < 15 && m[i + 1][j] == k - 1)
		{
			i = i + 1;
			the_path.push_back({ i, j });
			k -= 1;
		}
		else if (j < 15 && m[i][j + 1] == k - 1)
		{
			j = j + 1;
			the_path.push_back({ i, j });
			k -= 1;
		}
	}
	return the_path;
}

void drawPath(int(*map)[16], std::vector<Player::Coordinates> path)
{
	//Clear previous path
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
			if (map[i][j] == 5)
				map[i][j] = 0;

	// 5 represents pointer on the screen
	for (int i = 0; i < path.size(); ++i)
		map[path[i].x][path[i].y] = 5;
}

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 800), "Escape!");

	//Arrays that represent floors
	int map1[16][16] = {};
	int map2[16][16] = {};
	int map3[16][16] = {};
	createMap1(map1);
	createMap2(map2);
	createMap3(map3);

	Texture floorColor1;
	floorColor1.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\greenFloor.jpg");
	Texture floorColor2;
	floorColor2.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\yellowFloor.jpg");
	Texture floorColor3;
	floorColor3.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\blueFloor.jpg");
	Texture floorWall;
	floorWall.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\wall.jpg");
	Texture elevator;
	elevator.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\elevator3.png");
	Texture staircase;
	staircase.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\staircase2.png");
	Texture exit;
	exit.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\exit.png");
	Texture pointer;
	pointer.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\pointer.png");


	
	Texture specialStuff1;
	specialStuff1.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff1.png");
	Texture specialStuff2;
	specialStuff2.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff2.jpg");
	Texture specialStuff3;
	specialStuff3.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff3.jpg");
	Texture specialStuff4;
	specialStuff4.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff4.jpg");
	Texture specialStuff5;
	specialStuff5.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff5.jpg");
	Texture specialStuff6;
	specialStuff6.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\specialStuff6.jpg");
	
	Floor building[3];
	building[0] = Floor(floorColor1, floorWall, elevator, staircase, 0, exit, pointer, specialStuff1, specialStuff2, map3);
	building[1] = Floor(floorColor2, floorWall, elevator, staircase, 0, exit, pointer, specialStuff3, specialStuff4, map2);
	building[2] = Floor(floorColor3, floorWall, elevator, staircase, 0, exit, pointer, specialStuff5, specialStuff6, map1);

	Texture character;
	character.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\character.png");
	Player player{ character, {15, 3} };

	

	Player::Direction direction{ Player::NONE };

	Sprite buttonColor1{ floorColor1 };
	buttonColor1.setPosition(200.0f, 200.0f);
	setSpriteSize(buttonColor1, 100.0f, 100.0f);

	Sprite buttonColor2{ floorColor2 };
	buttonColor2.setPosition(400.0f, 200.0f);
	setSpriteSize(buttonColor2, 100.0f, 100.0f);

	Sprite buttonColor3{ floorColor3 };
	buttonColor3.setPosition(600.0f, 200.0f);
	setSpriteSize(buttonColor3, 100.0f, 100.0f);

	Sprite stuff1{ specialStuff1 };
	stuff1.setPosition(200.0f, 300.0f);
	setSpriteSize(stuff1, 100.0f, 100.0f);

	Sprite stuff2{ specialStuff2 };
	stuff2.setPosition(600.0f, 300.0f);
	setSpriteSize(stuff2, 100.0f, 100.0f);

	Sprite stuff3{ specialStuff3 };
	stuff3.setPosition(200.0f, 300.0f);
	setSpriteSize(stuff3, 100.0f, 100.0f);

	Sprite stuff4{ specialStuff4 };
	stuff4.setPosition(600.0f, 300.0f);
	setSpriteSize(stuff4, 100.0f, 100.0f);

	Sprite stuff5{ specialStuff5 };
	stuff5.setPosition(200.0f, 300.0f);
	setSpriteSize(stuff5, 100.0f, 100.0f);

	Sprite stuff6{ specialStuff6 };
	stuff6.setPosition(600.0f, 300.0f);
	setSpriteSize(stuff6, 100.0f, 100.0f);

	Texture digit_1;
	digit_1.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\digit_1.jpg");
	Texture digit_2;
	digit_2.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\digit_2.jpg");
	Texture digit_3;
	digit_3.loadFromFile("D:\\Labs\\semester_3\\AISD\\Lab1\\Lab1\\images\\digit_3.jpg");

	Sprite digit1{ digit_1 };
	digit1.setPosition(300.0f, 300.0f);
	setSpriteSize(digit1, 100.0f, 100.0f);
	Sprite digit2{ digit_2 };
	digit2.setPosition(405.0f, 300.0f);
	setSpriteSize(digit2, 100.0f, 100.0f);
	Sprite digit3{ digit_3 };
	digit3.setPosition(510.0f, 300.0f);
	setSpriteSize(digit3, 100.0f, 100.0f);

	
	int colorType;
	std::vector<Player::Coordinates> path;

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
			
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();

			if (event.type == Event::KeyPressed && gameState == MAIN)
			if (event.key.code == Keyboard::Up) direction = Player::UP;
			else if (event.key.code == Keyboard::Down) direction = Player::DOWN;
			else if (event.key.code == Keyboard::Left) direction = Player::LEFT;
			else if (event.key.code == Keyboard::Right) direction = Player::RIGHT;

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && gameState == GAME_START_COLOR_CHOICE)
			{
				if (sf::IntRect(200, 200, 100, 100).contains(sf::Mouse::getPosition(window)))
				{ 
					colorType = 0;
					player.setCurrentFloor(0); 
					gameState = GAME_START_STUFF_CHOICE; 
				}
				else if (sf::IntRect(400, 200, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					colorType = 1;
					player.setCurrentFloor(1);
					gameState = GAME_START_STUFF_CHOICE;
				}
				else if (sf::IntRect(600, 200, 100, 100).contains(sf::Mouse::getPosition(window))) 
				{ 
					colorType = 2;
					player.setCurrentFloor(2);
					gameState = GAME_START_STUFF_CHOICE;
				}
			}


			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && gameState == GAME_START_STUFF_CHOICE)
			{
				if (sf::IntRect(200, 300, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					
					switch (colorType)
					{
					case 0:
						player.setCoordinates({ 6,8 });
						break;
					case 1:
						player.setCoordinates({ 7,9 });
						break;
					case 2:
						player.setCoordinates({ 8,8 });
						break;
					}
				
					gameState = MAIN;
				}
				else if (sf::IntRect(600, 300, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					switch (colorType)
					{
					case 0:
						player.setCoordinates({ 13,4 });
						break;
					case 1:
						player.setCoordinates({ 13,4 });
						break;
					case 2:
						player.setCoordinates({ 13,2 });
						break;
					}
					gameState = MAIN;
				}
			}

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && gameState == ELEVATOR_MENU)
			{
				if (sf::IntRect(300, 300, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					player.setCurrentFloor(0);
					gameState = MAIN;
				}
				else if (sf::IntRect(405, 300, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					player.setCurrentFloor(1);
					gameState = MAIN;
				}
				else if (sf::IntRect(510, 300, 100, 100).contains(sf::Mouse::getPosition(window)))
				{
					player.setCurrentFloor(2);
					gameState = MAIN;
				}
			}

		}

		// Задаем цвет фона
		window.clear();
		switch (gameState)
		{
		case GAME_START_COLOR_CHOICE:
			window.draw(buttonColor1);
			window.draw(buttonColor2);
			window.draw(buttonColor3);
			break;
		case GAME_START_STUFF_CHOICE:
			switch (colorType)
			{
			case 0:
				window.draw(stuff1);
				window.draw(stuff2);
				break;
			case 1:
				window.draw(stuff3);
				window.draw(stuff4);
				break;
			case 2:
				window.draw(stuff5);
				window.draw(stuff6);
				break;
			}
			break;
		case MAIN:
			switch (player.getCurrentFloor())
			{
			case 0:
				path = findPath(building[player.getCurrentFloor()].m_map, player.getCoordinates(), { 15, 15 }, { 15, 15 });
				break;
			case 1:
				path = findPath(building[player.getCurrentFloor()].m_map, player.getCoordinates(), { 6, 0 }, { 7, 14 });
				break;
			case 2:
				path = findPath(building[player.getCurrentFloor()].m_map, player.getCoordinates(), { 3, 0 }, { 15, 15 });
				break;
			}
			drawPath(building[player.getCurrentFloor()].m_map, path);
			building[player.getCurrentFloor()].draw(window);
			player.move(window, building[player.getCurrentFloor()].m_map, direction);
			break;
		case ELEVATOR_MENU:
			building[player.getCurrentFloor()].draw(window);
			window.draw(digit1);
			window.draw(digit2);
			window.draw(digit3);

			break;
		}
			

		direction = Player::NONE;

		// Отрисовка окна	
		window.display();
	}

	return 0;
}

