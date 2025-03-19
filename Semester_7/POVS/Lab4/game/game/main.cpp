#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <asio.hpp>
#include <thread>
#include <mutex>
#include "view.h"
#include <sstream> // Ввод вывод текста С++
#include "missionName.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "level.h"
#include <vector>
#include <list>
#include <cctype>
#include "LifeBar.h"
#include "main.h"

using namespace sf;
using namespace std;

bool FirstShoot = false;
Clock timeShootC;

asio::io_service io;
asio::serial_port serial(io);
std::thread readerThread;

bool isJumpControllerButtonPressed = false;
bool isShootControllerButtonPressed = false;
bool isMooveRightJoystickPressed = false;
bool isMoovesLeftJoystickPressed = false;
bool isRun = false;

// Класс-родитель для всех персонажей(врагов, главного героя, платформ...)
class Entity {
public:
	/*
	* vector<Object> obj - вектор объектов карты
	* moveX, moveY - принимают значения скорости с знаком(вектор движения)
	* x, y - текущая координата спрайта персонажа
	* moveTimer - таймер обновления кадров
	* w, h - ширина и высота спрайта персонажа
	* health - здоровье персонажа
	* life - логическая переменная, отвечает за жизнь персонажа
	* isMove - логическая переменная, отвечает за движение персонажа
	* onGround - логическая переменная, отвечает за нахождение на земле
	* kickL, kickR, kickUp - логическая переменная, отвечает за подкидываение персонажа
	* texture, sprite, name - текстура, спрайт и имя персонажа
	*/
	vector<Object> obj;
	float moveX, moveY, x, y, moveSpeed, moveTimer; 
	int w, h, health;
	bool life, isMove, onGround, kickL, kickR, kickUp;
	Texture texture;
	Sprite sprite;
	String name;

	// Конструктор персонажа с инициализацией всех переменных
	Entity(Image& image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		moveSpeed = 0; health = 100; moveX = 0; moveY = 0;
		life = true; onGround = false; isMove = false;
		kickL = false;
		kickR = false;
		kickUp = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	// Функция. Возвращает координаты, ширину и высоту персонажа
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

	// Виртуальная процедура. Обновление всех персонажей
	virtual void update(float time) = 0;

};

// Класс главного героя:наследуется от класса персонажа
class Character:public Entity
{
public:
	// Перечислимый тип - отображает состояние главного героя
	enum stateObject { left, right, up, down, jump, stay }; 
	
	// Переменные перечислимого типа
	// Текущее состояние
	stateObject state;
	// Предыдущее состояние
	stateObject prevState; 
	
	// Количество очков главного героя
	int playerScore;
	
	// Логическая переменная. Отвечает за стрельбу г.г 
	bool isShoot;
	
	// Логическая переменная. Отвечает за переход на следующий уровень
	bool GoNextLevel;
	
	// Логические переменные. Отвечают за столкновение с конвеером
	bool collisTransporterR;
	bool collisTransporterL;
	
	// Текущий кадр г.г
	float CurrentFrame;

	// Конструктор г.г с инициализацией всех уникальных переменных
	Character(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		// Нахождение на прежнем уровне
		GoNextLevel = false;
		// Инициализация количества очков
		playerScore = 0;
		// Инициализация начального состояния
		state = right;
		// Инициализация стрельбы
		isShoot = false;
		//Движущиеся конвееры вправо и влево на втором уровне
		collisTransporterR = false;
		collisTransporterL = false;
		// Инициализация кадра
		CurrentFrame = 0;
		// Инициализация вектора. Получение всех объектов карты
		obj = lev.GetAllObjects(); 
		if (name == "Player1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	// Процедура. Обновление состояние персонажа
	void control(float time)
	{
		// При нажатии клавиши движения влево
		if (isMoovesLeftJoystickPressed)
		{
			// Обновление состояния
			state = left;
			// Если нажата клавиша ускорения 
			if (!isRun) {
				// Обновление анимации персонажа
				moveSpeed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 64, 256, -64, 64));
			}
			else
			{
				moveSpeed = 0.2;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 64, 256, -64, 64));
			}
		}
		// При нажатии клавиши движения вправо
		if (isMooveRightJoystickPressed)
		{
			state = right;
			if (!isRun) {
				moveSpeed = 0.1;
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 256, 64, 64));
			}
			else
			{
				moveSpeed = 0.2;
				CurrentFrame += 0.01 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 256, 64, 64));
			}
		}
		// При нажатии клавиши прыжка
		if ((isJumpControllerButtonPressed) && (onGround == true))
		{
			state = jump;
			moveY = -0.45;
			onGround = false;
			isJumpControllerButtonPressed = false;
		}
		// При нажатии клавиши движения вниз
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			state = down;
		}
		// При нажатии клавиши выстрела
		if ((isShootControllerButtonPressed) && (FirstShoot == false || timeShootC.getElapsedTime().asSeconds()>0.5)) {
			isShoot = true;
			isShootControllerButtonPressed = false;
		}
		// При отсутствии движения
		if (!isMoovesLeftJoystickPressed && !isMooveRightJoystickPressed
			&& !(Keyboard::isKeyPressed(Keyboard::W)) && !(Keyboard::isKeyPressed(Keyboard::S)))
		{
			state = prevState;
			if (prevState == right) 
			{
				CurrentFrame += 0.010 * time;
				if (CurrentFrame > 5)CurrentFrame -= 5;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 128, 64, 64));
			}
			if (prevState == left)
			{
				CurrentFrame += 0.010 * time;
				if (CurrentFrame > 5)CurrentFrame -= 5;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+64, 128, -64, 64));
			}
			
			
		}
	}
	// Процедура. Проверка столкновения с объектами карты
	void checkCollisionWithMap(float Dx, float Dy)
	{
		// Обход всех объектов карты
		for (int i = 0; i < obj.size(); i++)
			// При пересечении г.г и объектов карты
			if (getRect().intersects(obj[i].rect))
			{

				// Выталкивание персонажа из текстуры
				if (obj[i].name == "solid" || obj[i].name == "transporterR" || obj[i].name == "transporterL")
				{
					
					if (Dy > 0) { y = obj[i].rect.top - h;  moveY = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   moveY = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				// Передвижение г.г при пересечении с конвеерами
				if (obj[i].name == "transporterR")
				{
					collisTransporterR = true;
				}
				else
				{
					collisTransporterR = false;
				}
				if (obj[i].name == "transporterL")
				{
					collisTransporterL = true;
				}
				else
				{
					collisTransporterL = false;
				}
				if ((obj[i].name == "JumpPlatform") && (moveY > 0) && (onGround == false))
				{
					moveY = -0.8;
				}
				if (obj[i].name == "deathItem")
					health = 0;
				if (obj[i].name == "Exit")
					GoNextLevel = true;
				

			}
		
	}
	// Процедура. Обновляет вектор движения персонажа
	void update(float time)
	{
		prevState = state;
		// Обновление состояния персонажа
		control(time);
		// В зависимости от текущих состояния применение вектора движения
		switch (state)
		{
			case right:moveX = moveSpeed; break;
			case left: moveX = -moveSpeed; break;
			case up: break;
			case down: moveX = 0; break;
			case stay: moveX = 0;
		}
		if (kickUp) { moveY = -0.2; kickUp = false; }
		if (kickR) {
			moveX = 0.3;
		}
		if (kickL) {
			moveX = -0.3;
		}
		if (onGround) { kickR = false; kickL = false; }
		if (collisTransporterR == true)
		{
			x += 0.05 * time;
		}
		if (collisTransporterL == true)
		{
			x += -0.05 * time;
		} 

		// Изменение координат персонажа
		// Вектор(сокрость со знаком)*время + текущая координата = новая координата
		x += moveX*time;
		// Обработка столкновений по Ox
		checkCollisionWithMap(moveX, 0);
		// Изменение координат персонажа
		// Вектор(сокрость со знаком)*время + текущая координата = новая координата
		y += moveY*time;
		// Обработка столкновений по Oy
		checkCollisionWithMap(0, moveY);
		
		// Обновление позиций тайла
		sprite.setPosition(x + w / 2, y + h / 2);
		
		// Обновление состояния жизни, если персонаж мертв
		if (health <= 0) { life = false; }
		// Обновление состояния движения 
		if (!isMove) { moveSpeed = 0; }
		if (life) 
		{ 
			setCoordToView(x, y); 
			// scrollView(time);
		}
		// Создание гравитации, т е постоянное увеличение вектора движения вниз
		moveY = moveY + 0.0015*time;
		
	}

};

// Класс врага:наследуется от класса персонажа
class Enemy : public Entity {
public:
	// Время по прошествии которого меняется направление движения
	float timeToChange;
	// Текущий кадр анимации врага
	float CurrentFrame;
	// Конструктор класса врага. Инициализация всех уникальных переменных
	Enemy(Image& image, String Name,Level &lvl, float X, float Y, int W, int H,float Ti) :Entity(image, Name, X, Y, W, H) {
		//obj = lvl.GetObjects("solid"); 
		if (name == "EasyEnemy") 
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.1;
		}
		if (name == "RatEnemy")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.1;
		}
		if (name == "CyberEnemy")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.08;
		}
		if (name == "DroneEnemy1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.08;
		}
		if (name == "HelloweenEnemy1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.05;
		}
		if (name == "HelloweenEnemy2")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
			moveX = 0.08;
		}
		timeToChange = Ti;
	}

	// Взаимодействие с картой. 
	/* Замечание. В данной реализации процедура не используется. При необходимости,
	   смена направления движения врагов может происходить при столкновении с невидимыми или
	   видимыми объектами solid */
	void checkCollisionWithMap(float Dx, float Dy)
	{
		// Проход по всем объектам карты
		for (int i = 0; i < obj.size(); i++)
			// Проверка пересечения прямоугольника врага и препятствия
			if (getRect().intersects(obj[i].rect))
			{
				// Выталкивание прямоугольника врага из текстуры	
				if (Dy > 0) { y = obj[i].rect.top - h;  moveY = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   moveY = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  moveX = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; moveX = 0.1; sprite.scale(-1, 1); }

			}
	}

	// Процедура. Обновляет вектор движения персонажа
	void update(float time)
	{
		if (name == "EasyEnemy") {
			// Обноввление анимации врага
			if (moveX > 0) {
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 0, 64, 64));
			}
			else
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame)+64, 0, -64, 64));
			}

			// Смена направления движения врага по времени
			moveTimer += time;if (moveTimer>timeToChange){ moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);

			
			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}

		// Последующие враги - по аналогии с предыдущим
		if (name == "RatEnemy") 
		{
			if (moveX > 0) {
				CurrentFrame += 0.008 * time;
				if (CurrentFrame > 4)CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 32));
			}
			else
			{
				CurrentFrame += 0.008 * time;
				if (CurrentFrame > 4)CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 32, 0, -32, 32));
			}


			moveTimer += time; if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);

			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}

		if (name == "CyberEnemy")
		{
			if (moveX > 0) {
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 0, 64, 64));
			}
			else
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 64, 0, -64, 64));
			}


			moveTimer += time; if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);

			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}

		if (name == "DroneEnemy1")
		{
			if (moveX > 0) {
				CurrentFrame += 0.008 * time;
				if (CurrentFrame > 8)CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(48 * int(CurrentFrame), 0, 48, 48));
			}
			else
			{
				CurrentFrame += 0.008 * time;
				if (CurrentFrame > 8)CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(48 * int(CurrentFrame) + 48, 0, -48, 48));
			}


			moveTimer += time; if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);

			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}

		if (name == "HelloweenEnemy1")
		{
			if (moveX > 0) {
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 0, 64, 64));
			}
			else
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 64, 0, -64, 64));
			}


			moveTimer += time; if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);
			
			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}

		if (name == "HelloweenEnemy2")
		{
			if (moveX > 0) {
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame), 0, 64, 64));
			}
			else
			{
				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 6)CurrentFrame -= 6;
				sprite.setTextureRect(IntRect(64 * int(CurrentFrame) + 64, 0, -64, 64));
			}


			moveTimer += time; if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			// Обрабатываем столкновения по x
			//checkCollisionWithMap(moveX, 0);
			
			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}


		
	}
};
// Класс движущейся платформы:наследуется от класса персонажа
class MovingPlatform : public Entity {
public:
	// Тип платформы
	// type == 1 горизонтальная платформа
	// type == 2 вертикальная платформа
	int type;
	// Время по прошествии которого меняется направление движения
	float timeToChange;
	MovingPlatform(Image& image, String Name, Level& lvl, float X, float Y, int W, int H,int Tp,float Ti) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		type = Tp;
		// Инициализация начального вектора в зависимости от типа
		if(type==1)
			moveX = 0.08;
		if (type == 2)
			moveY = -0.08;
		timeToChange = Ti;
		
	}

	// Процедура. Обновляет вектор движения платформы
	void update(float time)
	{
		if(type==1)
		{
			x += moveX * time;
			moveTimer += time;
			if (moveTimer > timeToChange) { moveX *= -1; moveTimer = 0; }
			sprite.setPosition(x + w / 2, y + h / 2);
		}
		if (type == 2)
		{
			y += moveY * time;
			moveTimer += time;
			if (moveTimer > timeToChange) { moveY *= -1; moveTimer = 0; }
			sprite.setPosition(x + w / 2, y + h / 2);
		}

	}
};

// Класс пули: наследуется от класса персонажа
class Bullet : public Entity {
public:
	// Направление пули
	int direction;
	Sprite dopSprite;

	Bullet(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		// Инициализация объектов, с которыми взаимодействует пуля
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		direction = dir;
		moveSpeed = 0.8;
		w = h = 16;
		life = true;
		dopSprite = sprite;
	}

	// Процедура. Обновляет вектор движения пули
	void update(float time)
	{
		switch (direction)
		{
			case 0: moveX = -moveSpeed; moveY = 0;   break; // state = left
			case 1: moveX = moveSpeed; moveY = 0;   break;  //state = right
			case 2: moveX = 0; moveY = -moveSpeed;   break; //интовое значение state = up
			case 3: moveX = 0; moveY =  moveSpeed;   break;
			case 4: moveX = 0; moveY = -moveSpeed;   break;
			case 5: moveX = 0; moveY = -moveSpeed;   break;

		}
		if (moveX == 0 && moveY < 0) { sprite = dopSprite; sprite.setRotation(90); }
		else
		if (moveX == 0 && moveY > 0) { sprite = dopSprite; sprite.setRotation(-90); }
		else
		if (moveX < 0 && moveY == 0) { sprite = dopSprite; }
		else
		if (moveX > 0 && moveY == 0) { sprite = dopSprite; sprite.setRotation(180); }
		x += moveX * time;
		y += moveY * time;

		// Задержка пуль в стене
		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		// Обход всех solid объектов
		for (int i = 0; i < obj.size(); i++) {
			// При столкновении пули с объектом
			if (getRect().intersects(obj[i].rect)) 
			{
				// Пуля "умирает"
				life = false;
			}
		}


		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

// Класс монетки: наследуется от класса персонажа
class Coins : public Entity {
public:

	// Текущий кадр анимации монетки
	float CurrentFrame;
	Coins(Image& image, String Name, Level& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		CurrentFrame = 0;
	}

	// Процедура. Обновляет анимацию монетки
	void update(float time)
	{
		if (name == "Coin") {
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 6) CurrentFrame -= 6;
			sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 0, 24, 24));
			sprite.setPosition(x + w / 2, y + h / 2);
		}
		if (name == "Card") {
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(24 * int(CurrentFrame), 0, 24, 24));
			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}
};

// Класс пресса :наследуется от класса персонажа
class Hammer : public Entity {
public:
	// Текущий кадр анимации пресса
	float CurrentFrame;
	// Время по прошествии которого меняется направление движения
	float timeToChange;
	Hammer(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, float Ti) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		moveY = 0.08;
		timeToChange = Ti;
		CurrentFrame = 0;
	}

	// Процедура. Обновляет анимацию пресса
	void update(float time)
	{
			CurrentFrame += 0.0040 * time;
			if (CurrentFrame > 8)CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 64));
			
			y += moveY * time;
			moveTimer += time;
			if (moveTimer > timeToChange) { moveY *= -1; moveTimer = 0; }
			sprite.setPosition(x + w/2, y + h/2);
	}
};

// Процедура. Отвечает за загрузку уровня
void changeLevel(Level& lvl, int& numberLevel)
{
	switch (numberLevel)
	{
	case 1:
	{
		lvl.LoadFromFile("map1.tmx");
		break;
	}
	case 2:
	{
		lvl.LoadFromFile("map2.tmx");
		break;
	}
	case 3:
	{
		lvl.LoadFromFile("map3.tmx");
		break;
	}
	case 4:
	{
		lvl.LoadFromFile("about.tmx");
		break;
	}
	default:
		exit;
	}
}
// Процедура. Обновляет анимаци выходов с уровней
void updateExit(float time, float &CurrentFrameExit, int numberLevel,Sprite &exitSprite)
{
	
	if (numberLevel == 1) 
	{
		CurrentFrameExit += 0.005 * time;
		if (CurrentFrameExit > 4) CurrentFrameExit -= 4;
		exitSprite.setTextureRect(IntRect(64 * int(CurrentFrameExit), 0, 64, 64));
	}
	if (numberLevel == 2)
	{
		CurrentFrameExit += 0.005 * time;
		if (CurrentFrameExit > 4) CurrentFrameExit -= 4;
		exitSprite.setTextureRect(IntRect(32 * int(CurrentFrameExit), 0, 32, 42));
	}
	if (numberLevel == 3)
	{
		CurrentFrameExit += 0.005 * time;
		if (CurrentFrameExit > 4) CurrentFrameExit -= 4;
		exitSprite.setTextureRect(IntRect(82 * int(CurrentFrameExit), 0, 82, 64));
	}

}

// Function to configure the serial port
void configureSerialPort(asio::serial_port& serial,
	const string& portname,
	unsigned int baud_rate)
{
	// Open the specified serial port
	serial.open(portname);
	// Set the baud rate
	serial.set_option(
		asio::serial_port_base::baud_rate(baud_rate));
}

std::string serialData;
std::mutex dataMutex;

void readFromSerialPort(asio::serial_port& serial) {
	char buf[1024];
	asio::error_code ec;

	while (true) {
		size_t bytes_read = serial.read_some(asio::buffer(buf), ec);

		if (!ec) {
			std::lock_guard<std::mutex> lock(dataMutex);
			serialData = string{ buf, bytes_read };
		}
		else {
			std::cerr << "Read error: " << ec.message() << std::endl;
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

std::vector<std::string> splitString(const std::string& input) {
	std::vector<std::string> result;
	std::istringstream stream(input);
	std::string token;

	while (std::getline(stream, token, '\n')) {
		result.push_back(token);
	}

	return result;
}

int startGame(RenderWindow &window,int &numberLevel)
{

	// Инициализация камеры
	view.reset(FloatRect(0, 0, 1280, 720));

	// Создание экземпляра класса "уровень"
	Level lvl;
	// Загрузка самой карты уровня
	changeLevel(lvl, numberLevel);

	// Блок загрузки звуков и музыки
	// 1) Выстрелы -
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sounds/shoot.ogg");
	Sound shoot(shootBuffer);
	shoot.setVolume(40);
	// 2) Музыка самой игры
	Music music;
	music.openFromFile("sounds/ClashMusic.wav");
	music.play();
	music.setLoop(true);

	// Блок загрузки шрифтов и создание текста
	// Создание по умолчанию пустого шрифта
	Font font;
	font.loadFromFile("fonts/Inkulinati-Regular.otf");
	// Иниц. значение, шрифт, размер(для сундуков)
	Text txt1("", font, 22);
	txt1.setFillColor(Color::Red);
	txt1.setStyle(Text::Bold);
	// Здоровье
	Text txt2("", font, 22);
	txt2.setFillColor(Color::Red);
	txt2.setStyle(Text::Bold);
	// Время игры
	Text txt3("", font, 22);
	txt3.setFillColor(Color::Red);
	txt3.setStyle(Text::Bold);
	// Текст миссии
	Text txt4("", font, 30);
	txt4.setFillColor(Color::Black);
	txt4.setStyle(Text::Bold);

	// Для обеспечения большей плавности работа со временем
	Clock clock;

	// Время игры
	Clock timeGame;

	// Время жизни персонажа в секундах
	int timePlayerAlive = 0;

	// Текущий кадр анимации персонажа и выходов
	float CurrentFrame = 0;
	float CurrentFrameExit = 0;

	// Секция задания текста 
	Image missionImage;
	missionImage.loadFromFile("images/mission.jpg");
	missionImage.createMaskFromColor(Color(0, 0, 0));
	Texture missionTexture;
	missionTexture.loadFromImage(missionImage);
	Sprite missionSprite;
	missionSprite.setTexture(missionTexture);
	missionSprite.setTextureRect(IntRect(0, 0, 300, 300));
	//	missionSprite.setScale(0.6f, 0.6f);

	// Логическая переменная, отвечающая за появление текста 
	bool showMissionText = true;

	// Загрузка общих картинок
	Image heroImage;
	heroImage.loadFromFile("images/hero2.png");
	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	Image CoinImage;
	CoinImage.loadFromFile("images/Money.png");
	
	// Загрузка особых картинок
	Image CardImage;
	Image movePlatformImage;
	Image RatEnemyImage;
	Image exitImage;
	Image easyEnemyImage;
	Image cyberEnemyImage;
	Image droneEnemy1Image;
	Image hammerImage;
	Image HelloweenEnemy1Image;
	Image HelloweenEnemy2Image;

	// Время движения платформ для каждого уровня
	int platfotmUpDown;
	int platformRightLeft;
	if (numberLevel == 1)
	{
		CardImage.loadFromFile("images/Card.png");
		movePlatformImage.loadFromFile("images/movingPlatform.png");
		RatEnemyImage.loadFromFile("images/RatEnemy.png");
		platformRightLeft = 2000;
		platfotmUpDown = 2000;
		exitImage.loadFromFile("images/Exit1.png");
		easyEnemyImage.loadFromFile("images/EasyEnemyGW.png");
	}
	if (numberLevel == 2)
	{
		CardImage.loadFromFile("images/Card2.png");
		movePlatformImage.loadFromFile("images/movingPlatform2.png");
		RatEnemyImage.loadFromFile("images/RatEnemy2.png");
		platformRightLeft = 1300;
		platfotmUpDown = 1300;
		exitImage.loadFromFile("images/Exit2.png");
		cyberEnemyImage.loadFromFile("images/CyberEnemy.png");
		droneEnemy1Image.loadFromFile("images/DroneEnemy1.png");
		hammerImage.loadFromFile("images/Hammer.png");
	}
	if (numberLevel == 3)
	{
		CardImage.loadFromFile("images/Card.png");
		movePlatformImage.loadFromFile("images/movingPlatform.png");
		RatEnemyImage.loadFromFile("images/RatEnemy.png");
		platformRightLeft = 2000;
		platfotmUpDown = 2000;
		exitImage.loadFromFile("images/Exit3.png");
		HelloweenEnemy1Image.loadFromFile("images/HelloweenEnemy1.png");
		HelloweenEnemy2Image.loadFromFile("images/HelloweenEnemy2.png");

	}
	Texture exitTexture;
	exitTexture.loadFromImage(exitImage);
	Sprite exitSprite;
	exitSprite.setTexture(exitTexture);
	if(numberLevel == 1)
		exitSprite.setPosition(lvl.GetObject("Exit").rect.left-40, lvl.GetObject("Exit").rect.top);
	if(numberLevel == 2)
		exitSprite.setPosition(lvl.GetObject("Exit").rect.left -20, lvl.GetObject("Exit").rect.top);
	if (numberLevel == 3)
		exitSprite.setPosition(lvl.GetObject("Exit").rect.left-35, lvl.GetObject("Exit").rect.top-5);
	exitSprite.setTextureRect(IntRect(0, 0, lvl.GetObject("Exit").rect.width, lvl.GetObject("Exit").rect.height));

	// Создание полоски здоровья
	LifeBar lifeBarPlayer;


	
	// Список для объектов(враги, пули, платформы, монеты)
	list<Entity*>  entities;
	// Итераторы прохода по всем элементам списка
	list<Entity*>::iterator it;
	list<Entity*>::iterator it2;

	// Последовательная загрузка всех объектов в вектор
	vector<Object> e = lvl.GetObjects("EasyEnemy");
	// Проход по всем элементам вектора
	for (int i = 0; i < e.size(); i++)
		// Добавление в список врагов из вектора
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 64, 64,3000));

	// Аналогично с другими объектами
	e = lvl.GetObjects("RatEnemy");
	for (int i = 0; i < e.size(); i++)
		// Добавляем в список врагов из вектора
		entities.push_back(new Enemy(RatEnemyImage, "RatEnemy", lvl, e[i].rect.left, e[i].rect.top, 32, 32, 1000));

	e = lvl.GetObjects("CyberEnemy");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Enemy(cyberEnemyImage, "CyberEnemy", lvl, e[i].rect.left, e[i].rect.top, 64, 64, 1500));
	
	e = lvl.GetObjects("DroneEnemy1");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new Enemy(droneEnemy1Image, "DroneEnemy1", lvl, e[i].rect.left, e[i].rect.top, 42, 48, 1500));

	e = lvl.GetObjects("HelloweenEnemy1");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new Enemy(HelloweenEnemy1Image, "HelloweenEnemy1", lvl, e[i].rect.left, e[i].rect.top, 64, 70, 1200));
	
	e = lvl.GetObjects("HelloweenEnemy2");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new Enemy(HelloweenEnemy2Image, "HelloweenEnemy2", lvl, e[i].rect.left, e[i].rect.top, 64, 64, 3000));

	e = lvl.GetObjects("MovingPlatform1");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new MovingPlatform(movePlatformImage, "MovingPlatform", lvl, e[i].rect.left, e[i].rect.top, 95, 22,1,platformRightLeft));
	
	e = lvl.GetObjects("MovingPlatform2");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new MovingPlatform(movePlatformImage, "MovingPlatform", lvl, e[i].rect.left, e[i].rect.top, 95, 22, 2,platfotmUpDown));

	e = lvl.GetObjects("Card");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Coins(CardImage, "Card", lvl, e[i].rect.left, e[i].rect.top, 24, 24));

	e = lvl.GetObjects("Coin");
	for (int i = 0; i < e.size(); i++) 
		entities.push_back(new Coins(CoinImage, "Coin", lvl, e[i].rect.left, e[i].rect.top, 24, 24));
	
	e = lvl.GetObjects("Hammer");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Hammer(hammerImage, "Hammer", lvl, e[i].rect.left, e[i].rect.top, 25, 55,1000));

	// Загрузка объекта главного героя с карты
	Object player = lvl.GetObject("player");
	// Создание программного объекта главного героя
	Character p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 55, 52);


	window.setFramerateLimit(120.0f);
	// Цикл обновление окна, пока оно открыто
	while (window.isOpen())
	{
		std::string currentData;
		{
			std::lock_guard<std::mutex> lock(dataMutex);
			currentData = serialData;
		}
		if (!currentData.empty()) {
			std::vector<std::string> lines = splitString(currentData);
			for (const auto& line : lines) {
				if (line == "stand") {
					std::cout << line;
					isMooveRightJoystickPressed = false;
					isMoovesLeftJoystickPressed = false;
					//isRun = false;
				} 
				else if (line == "moveRight") {
					std::cout << line;
					isMooveRightJoystickPressed = true;
					isMoovesLeftJoystickPressed = false;
				} 
				else if (line == "moveLeft") {
					std::cout << line;
					isMoovesLeftJoystickPressed = true;
					isMooveRightJoystickPressed = false;
				}
				if (line == "jump") {
					std::cout << line;
					isJumpControllerButtonPressed = true;
				}
				if (line == "shoot") {
					std::cout << line;
					isShootControllerButtonPressed = true;
				}
				if (line == "switchRun") {
					isRun = !isRun;
				} 
			}
			serialData.clear();
			currentData.clear();

		}

		// Получение прошедшего времени в микросекундах
		float time = clock.getElapsedTime().asMicroseconds();

		// Обновление времени жизни персонажа, пока он жив
		if (p.life == true)
			timePlayerAlive = timeGame.getElapsedTime().asSeconds();

		// Перезагрузка времени
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				readerThread.detach();
				serial.close();
				window.close();
			}

		}

		// При условии, что был выстрел
		if (p.isShoot == true)
		{

			// Создание объекта пули
			p.isShoot = false;
			entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x + 38, p.y + 19, 31, 16, p.state));
			shoot.play();
			FirstShoot = true;
			timeShootC.restart();
		}

		// Обновление здоровья персонажа
		lifeBarPlayer.update(p.health);

		// Проход по всем элементам главного списка entities
		for (it = entities.begin(); it != entities.end();)
		{
			// Для удобства обращения к указателю на указатель, чтобы не писать (*it)->
			Entity* b = *it;

			// Запуск обновления всех динамических объектов на карте
			b->update(time);
			
			// Если объект мертв, удаление из списка
			if (b->life == false) 
			{
				it = entities.erase(it); delete b; 
			}
			// Переход к следующему объекту
			else it++;
		}

		// Проход по всем элементам главного списка entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// Проверка столкновения г.г и движущейся платформы
			if (((*it)->name == "MovingPlatform") && ((*it)->getRect().intersects(p.getRect())))
			{
				Entity* movPlat = *it;
				// Если г.г не на земле и летит вниз
				if (((p.moveY > 0) || (p.onGround == false))&&(p.moveY>=0))
					if (p.y + p.h < movPlat->y + movPlat->h)
					{
						// Выталкивание из платформы и установка состояния "на земле" для г.г
						p.y = movPlat->y - p.h + 0.1; p.x += movPlat->moveX * time; p.moveY = 0;
						p.onGround = true; 
					}
			}
		


			// Проверка пересечения врагов и г.г
			if ((((*it)->name == "EasyEnemy") || ((*it)->name == "RatEnemy") || ((*it)->name == "CyberEnemy") || ((*it)->name == "DroneEnemy1") || ((*it)->name == "HelloweenEnemy1") || ((*it)->name == "HelloweenEnemy2")) && ((*it)->getRect().intersects(p.getRect())))
			{
				// Если г.г напрыгнул сверхку, то враг умирает
				if ((p.moveY > 0) && (p.onGround == false)) {
					(*it)->moveX = 0; p.moveY = -0.4; (*it)->health = 0;
				}
				// Если г.г и враг столкнулись боком, то персонаж отталкивается и теряет здоровье
				if ((*it)->moveX > 0) {
					if (p.moveX <= 0)
					{
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 10;
					} else
					if (p.moveX > 0)
					{
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 10;
					}

				}
				if ((*it)->moveX < 0) {
					if (p.moveX >= 0)
					{
						p.kickL = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 10;
					} else
					if (p.moveX < 0)
					{
						p.kickR = true; p.kickUp = true;
						p.onGround = false;
						p.health -= 10;
					}

				}
			}
			// Проверка пересечения пресса и персонажа
			if ((((*it)->name == "Hammer")) && ((*it)->getRect().intersects(p.getRect())))
			{
				p.health = 0;
			}
			// Проверка пересечения монетки и персонажа
			if ((((*it)->name == "Coin")) && ((*it)->getRect().intersects(p.getRect())))
			{
				(*it)->life = false;
				p.playerScore++;
			}
			// Проверка пересечения карточки и персонажа
			if ((((*it)->name == "Card")) && ((*it)->getRect().intersects(p.getRect())))
			{
				(*it)->life = false;
				p.playerScore += 5;
			}
			

			// Вложенный цикл прохода по всем элементам списка entities
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				// Если между собой объекты столкнулись
				if ((*it)->getRect() != (*it2)->getRect())
					// Если это пуля и любой враг
					if (((*it)->getRect().intersects((*it2)->getRect())) && (((*it)->name == "EasyEnemy") || ((*it)->name == "CyberEnemy") || ((*it)->name == "DroneEnemy1") || ((*it)->name == "HelloweenEnemy1") || ((*it)->name == "HelloweenEnemy2")) && ((*it2)->name == "Bullet"))
					{
						// Убавление здоровья врага и смерть пули
						(*it)->health -= 50; 
						(*it2)->life = false;
						// Примечение. Тут может быть любое значение урона пули
					}
			}
		}

		// Блок принятия решений по завершению уровня
		if (p.health<=0 || Keyboard::isKeyPressed(Keyboard::R))
		{ 
			return 1; 
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{ 
			return 2; 
		}
		if (p.GoNextLevel == true)
		{
			p.GoNextLevel = false;
			return 3;
		}

		// Обновление г.г и выхода
		updateExit(time, CurrentFrameExit, numberLevel, exitSprite);
		p.update(time);

		// Установка камеры
		window.setView(view);

		// Очистка окна и его перерисовка
		if(numberLevel == 1)
			window.clear(Color(204, 226, 225));
		if (numberLevel == 2)
			window.clear(Color(179, 175, 189));
		if (numberLevel == 3 || numberLevel == 4)
			window.clear(Color(124, 110, 122));
		
		// Рисование уровня
		lvl.Draw(window); 

		// Рисование обновленных объектов уровня
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
		}
		// Рисование выхода и г.г
		window.draw(exitSprite);
		window.draw(p.sprite);
		

		// Обновление текста очков
		txt1.setString("Found money: " + to_string(p.playerScore));
		txt1.setPosition(view.getCenter().x - 590, view.getCenter().y - 350);
		window.draw(txt1);

		// Обновление текста здоровья
		txt2.setString("Health: " + to_string(p.health));
		txt2.setPosition(view.getCenter().x - 590, view.getCenter().y - 325);
		window.draw(txt2);

		// Обновление текста ко-ва времени
		txt3.setString("Time: " + to_string(timePlayerAlive));
		txt3.setPosition(view.getCenter().x - 590, view.getCenter().y - 300);
		window.draw(txt3);

		// Обновление текста миссии и позицию его фона
		if (!showMissionText)
		{
			// Устанавливка позиции текста и спрайта фона текста
			txt4.setPosition(view.getCenter().x + 355, view.getCenter().y - 360);
			missionSprite.setPosition(view.getCenter().x + 340, view.getCenter().y - 360);
			// Перерисовка
			window.draw(missionSprite);
			window.draw(txt4);
		}


		// Перерисовка здоровья
		lifeBarPlayer.draw(window);
		window.display();

	}
}

// Процедура перезапуска игры, если это необходимо
void gameRunning(RenderWindow &window,int & numberLevel) {
	int run = startGame(window, numberLevel);
	// gameOption == 1 - рестарт текущего уровня
	// gameOption == 2 - Выход из игры
	// gameOption == 3 - запуск следующего уровня
	// gameOption == 4 - запуск уровня about program
	// gameOption == 5 - рестарт всей игры
	if (run == 1) 
	{	
		gameRunning(window,numberLevel); 
	} 
	if (run == 2)
	{
		readerThread.detach();
		serial.close();
		exit;
	} 
	if (run == 3)
	{
		++numberLevel;
		gameRunning(window, numberLevel);
	}
	
}

int main()
{	
	try {
		configureSerialPort(serial, "COM5", 115200);
	}
	catch (const exception& e) {
		cerr << "Error configuring serial port: "
			<< e.what() << endl;
		return 1;
	}
	readerThread = std::thread{ readFromSerialPort, std::ref(serial) };

	RenderWindow window(VideoMode(1280, 720), "game");
	// Сначала загрузка первого уровня
	int numberLevel = 1;
	gameRunning(window,numberLevel);
	return 0;
}