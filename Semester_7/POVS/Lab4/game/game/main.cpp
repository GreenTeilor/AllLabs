#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <asio.hpp>
#include <thread>
#include <mutex>
#include "view.h"
#include <sstream> // ���� ����� ������ �++
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

// �����-�������� ��� ���� ����������(������, �������� �����, ��������...)
class Entity {
public:
	/*
	* vector<Object> obj - ������ �������� �����
	* moveX, moveY - ��������� �������� �������� � ������(������ ��������)
	* x, y - ������� ���������� ������� ���������
	* moveTimer - ������ ���������� ������
	* w, h - ������ � ������ ������� ���������
	* health - �������� ���������
	* life - ���������� ����������, �������� �� ����� ���������
	* isMove - ���������� ����������, �������� �� �������� ���������
	* onGround - ���������� ����������, �������� �� ���������� �� �����
	* kickL, kickR, kickUp - ���������� ����������, �������� �� ������������� ���������
	* texture, sprite, name - ��������, ������ � ��� ���������
	*/
	vector<Object> obj;
	float moveX, moveY, x, y, moveSpeed, moveTimer; 
	int w, h, health;
	bool life, isMove, onGround, kickL, kickR, kickUp;
	Texture texture;
	Sprite sprite;
	String name;

	// ����������� ��������� � �������������� ���� ����������
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

	// �������. ���������� ����������, ������ � ������ ���������
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

	// ����������� ���������. ���������� ���� ����������
	virtual void update(float time) = 0;

};

// ����� �������� �����:����������� �� ������ ���������
class Character:public Entity
{
public:
	// ������������ ��� - ���������� ��������� �������� �����
	enum stateObject { left, right, up, down, jump, stay }; 
	
	// ���������� ������������� ����
	// ������� ���������
	stateObject state;
	// ���������� ���������
	stateObject prevState; 
	
	// ���������� ����� �������� �����
	int playerScore;
	
	// ���������� ����������. �������� �� �������� �.� 
	bool isShoot;
	
	// ���������� ����������. �������� �� ������� �� ��������� �������
	bool GoNextLevel;
	
	// ���������� ����������. �������� �� ������������ � ���������
	bool collisTransporterR;
	bool collisTransporterL;
	
	// ������� ���� �.�
	float CurrentFrame;

	// ����������� �.� � �������������� ���� ���������� ����������
	Character(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
		// ���������� �� ������� ������
		GoNextLevel = false;
		// ������������� ���������� �����
		playerScore = 0;
		// ������������� ���������� ���������
		state = right;
		// ������������� ��������
		isShoot = false;
		//���������� �������� ������ � ����� �� ������ ������
		collisTransporterR = false;
		collisTransporterL = false;
		// ������������� �����
		CurrentFrame = 0;
		// ������������� �������. ��������� ���� �������� �����
		obj = lev.GetAllObjects(); 
		if (name == "Player1")
		{
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	// ���������. ���������� ��������� ���������
	void control(float time)
	{
		// ��� ������� ������� �������� �����
		if (isMoovesLeftJoystickPressed)
		{
			// ���������� ���������
			state = left;
			// ���� ������ ������� ��������� 
			if (!isRun) {
				// ���������� �������� ���������
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
		// ��� ������� ������� �������� ������
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
		// ��� ������� ������� ������
		if ((isJumpControllerButtonPressed) && (onGround == true))
		{
			state = jump;
			moveY = -0.45;
			onGround = false;
			isJumpControllerButtonPressed = false;
		}
		// ��� ������� ������� �������� ����
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			state = down;
		}
		// ��� ������� ������� ��������
		if ((isShootControllerButtonPressed) && (FirstShoot == false || timeShootC.getElapsedTime().asSeconds()>0.5)) {
			isShoot = true;
			isShootControllerButtonPressed = false;
		}
		// ��� ���������� ��������
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
	// ���������. �������� ������������ � ��������� �����
	void checkCollisionWithMap(float Dx, float Dy)
	{
		// ����� ���� �������� �����
		for (int i = 0; i < obj.size(); i++)
			// ��� ����������� �.� � �������� �����
			if (getRect().intersects(obj[i].rect))
			{

				// ������������ ��������� �� ��������
				if (obj[i].name == "solid" || obj[i].name == "transporterR" || obj[i].name == "transporterL")
				{
					
					if (Dy > 0) { y = obj[i].rect.top - h;  moveY = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   moveY = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				// ������������ �.� ��� ����������� � ����������
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
	// ���������. ��������� ������ �������� ���������
	void update(float time)
	{
		prevState = state;
		// ���������� ��������� ���������
		control(time);
		// � ����������� �� ������� ��������� ���������� ������� ��������
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

		// ��������� ��������� ���������
		// ������(�������� �� ������)*����� + ������� ���������� = ����� ����������
		x += moveX*time;
		// ��������� ������������ �� Ox
		checkCollisionWithMap(moveX, 0);
		// ��������� ��������� ���������
		// ������(�������� �� ������)*����� + ������� ���������� = ����� ����������
		y += moveY*time;
		// ��������� ������������ �� Oy
		checkCollisionWithMap(0, moveY);
		
		// ���������� ������� �����
		sprite.setPosition(x + w / 2, y + h / 2);
		
		// ���������� ��������� �����, ���� �������� �����
		if (health <= 0) { life = false; }
		// ���������� ��������� �������� 
		if (!isMove) { moveSpeed = 0; }
		if (life) 
		{ 
			setCoordToView(x, y); 
			// scrollView(time);
		}
		// �������� ����������, � � ���������� ���������� ������� �������� ����
		moveY = moveY + 0.0015*time;
		
	}

};

// ����� �����:����������� �� ������ ���������
class Enemy : public Entity {
public:
	// ����� �� ���������� �������� �������� ����������� ��������
	float timeToChange;
	// ������� ���� �������� �����
	float CurrentFrame;
	// ����������� ������ �����. ������������� ���� ���������� ����������
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

	// �������������� � ������. 
	/* ���������. � ������ ���������� ��������� �� ������������. ��� �������������,
	   ����� ����������� �������� ������ ����� ����������� ��� ������������ � ���������� ���
	   �������� ��������� solid */
	void checkCollisionWithMap(float Dx, float Dy)
	{
		// ������ �� ���� �������� �����
		for (int i = 0; i < obj.size(); i++)
			// �������� ����������� �������������� ����� � �����������
			if (getRect().intersects(obj[i].rect))
			{
				// ������������ �������������� ����� �� ��������	
				if (Dy > 0) { y = obj[i].rect.top - h;  moveY = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   moveY = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w;  moveX = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; moveX = 0.1; sprite.scale(-1, 1); }

			}
	}

	// ���������. ��������� ������ �������� ���������
	void update(float time)
	{
		if (name == "EasyEnemy") {
			// ����������� �������� �����
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

			// ����� ����������� �������� ����� �� �������
			moveTimer += time;if (moveTimer>timeToChange){ moveX *= -1; moveTimer = 0; }
			// ������������ ������������ �� x
			//checkCollisionWithMap(moveX, 0);

			
			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2); 
			if (health <= 0) { life = false; }
		}

		// ����������� ����� - �� �������� � ����������
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
			// ������������ ������������ �� x
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
			// ������������ ������������ �� x
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
			// ������������ ������������ �� x
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
			// ������������ ������������ �� x
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
			// ������������ ������������ �� x
			//checkCollisionWithMap(moveX, 0);
			
			x += moveX * time;

			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}


		
	}
};
// ����� ���������� ���������:����������� �� ������ ���������
class MovingPlatform : public Entity {
public:
	// ��� ���������
	// type == 1 �������������� ���������
	// type == 2 ������������ ���������
	int type;
	// ����� �� ���������� �������� �������� ����������� ��������
	float timeToChange;
	MovingPlatform(Image& image, String Name, Level& lvl, float X, float Y, int W, int H,int Tp,float Ti) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		type = Tp;
		// ������������� ���������� ������� � ����������� �� ����
		if(type==1)
			moveX = 0.08;
		if (type == 2)
			moveY = -0.08;
		timeToChange = Ti;
		
	}

	// ���������. ��������� ������ �������� ���������
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

// ����� ����: ����������� �� ������ ���������
class Bullet : public Entity {
public:
	// ����������� ����
	int direction;
	Sprite dopSprite;

	Bullet(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		// ������������� ��������, � �������� ��������������� ����
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		direction = dir;
		moveSpeed = 0.8;
		w = h = 16;
		life = true;
		dopSprite = sprite;
	}

	// ���������. ��������� ������ �������� ����
	void update(float time)
	{
		switch (direction)
		{
			case 0: moveX = -moveSpeed; moveY = 0;   break; // state = left
			case 1: moveX = moveSpeed; moveY = 0;   break;  //state = right
			case 2: moveX = 0; moveY = -moveSpeed;   break; //������� �������� state = up
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

		// �������� ���� � �����
		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		// ����� ���� solid ��������
		for (int i = 0; i < obj.size(); i++) {
			// ��� ������������ ���� � ��������
			if (getRect().intersects(obj[i].rect)) 
			{
				// ���� "�������"
				life = false;
			}
		}


		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

// ����� �������: ����������� �� ������ ���������
class Coins : public Entity {
public:

	// ������� ���� �������� �������
	float CurrentFrame;
	Coins(Image& image, String Name, Level& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		CurrentFrame = 0;
	}

	// ���������. ��������� �������� �������
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

// ����� ������ :����������� �� ������ ���������
class Hammer : public Entity {
public:
	// ������� ���� �������� ������
	float CurrentFrame;
	// ����� �� ���������� �������� �������� ����������� ��������
	float timeToChange;
	Hammer(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, float Ti) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));
		moveY = 0.08;
		timeToChange = Ti;
		CurrentFrame = 0;
	}

	// ���������. ��������� �������� ������
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

// ���������. �������� �� �������� ������
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
// ���������. ��������� ������� ������� � �������
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

	// ������������� ������
	view.reset(FloatRect(0, 0, 1280, 720));

	// �������� ���������� ������ "�������"
	Level lvl;
	// �������� ����� ����� ������
	changeLevel(lvl, numberLevel);

	// ���� �������� ������ � ������
	// 1) �������� -
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sounds/shoot.ogg");
	Sound shoot(shootBuffer);
	shoot.setVolume(40);
	// 2) ������ ����� ����
	Music music;
	music.openFromFile("sounds/ClashMusic.wav");
	music.play();
	music.setLoop(true);

	// ���� �������� ������� � �������� ������
	// �������� �� ��������� ������� ������
	Font font;
	font.loadFromFile("fonts/Inkulinati-Regular.otf");
	// ����. ��������, �����, ������(��� ��������)
	Text txt1("", font, 22);
	txt1.setFillColor(Color::Red);
	txt1.setStyle(Text::Bold);
	// ��������
	Text txt2("", font, 22);
	txt2.setFillColor(Color::Red);
	txt2.setStyle(Text::Bold);
	// ����� ����
	Text txt3("", font, 22);
	txt3.setFillColor(Color::Red);
	txt3.setStyle(Text::Bold);
	// ����� ������
	Text txt4("", font, 30);
	txt4.setFillColor(Color::Black);
	txt4.setStyle(Text::Bold);

	// ��� ����������� ������� ��������� ������ �� ��������
	Clock clock;

	// ����� ����
	Clock timeGame;

	// ����� ����� ��������� � ��������
	int timePlayerAlive = 0;

	// ������� ���� �������� ��������� � �������
	float CurrentFrame = 0;
	float CurrentFrameExit = 0;

	// ������ ������� ������ 
	Image missionImage;
	missionImage.loadFromFile("images/mission.jpg");
	missionImage.createMaskFromColor(Color(0, 0, 0));
	Texture missionTexture;
	missionTexture.loadFromImage(missionImage);
	Sprite missionSprite;
	missionSprite.setTexture(missionTexture);
	missionSprite.setTextureRect(IntRect(0, 0, 300, 300));
	//	missionSprite.setScale(0.6f, 0.6f);

	// ���������� ����������, ���������� �� ��������� ������ 
	bool showMissionText = true;

	// �������� ����� ��������
	Image heroImage;
	heroImage.loadFromFile("images/hero2.png");
	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	Image CoinImage;
	CoinImage.loadFromFile("images/Money.png");
	
	// �������� ������ ��������
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

	// ����� �������� �������� ��� ������� ������
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

	// �������� ������� ��������
	LifeBar lifeBarPlayer;


	
	// ������ ��� ��������(�����, ����, ���������, ������)
	list<Entity*>  entities;
	// ��������� ������� �� ���� ��������� ������
	list<Entity*>::iterator it;
	list<Entity*>::iterator it2;

	// ���������������� �������� ���� �������� � ������
	vector<Object> e = lvl.GetObjects("EasyEnemy");
	// ������ �� ���� ��������� �������
	for (int i = 0; i < e.size(); i++)
		// ���������� � ������ ������ �� �������
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 64, 64,3000));

	// ���������� � ������� ���������
	e = lvl.GetObjects("RatEnemy");
	for (int i = 0; i < e.size(); i++)
		// ��������� � ������ ������ �� �������
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

	// �������� ������� �������� ����� � �����
	Object player = lvl.GetObject("player");
	// �������� ������������ ������� �������� �����
	Character p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 55, 52);


	window.setFramerateLimit(120.0f);
	// ���� ���������� ����, ���� ��� �������
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

		// ��������� ���������� ������� � �������������
		float time = clock.getElapsedTime().asMicroseconds();

		// ���������� ������� ����� ���������, ���� �� ���
		if (p.life == true)
			timePlayerAlive = timeGame.getElapsedTime().asSeconds();

		// ������������ �������
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

		// ��� �������, ��� ��� �������
		if (p.isShoot == true)
		{

			// �������� ������� ����
			p.isShoot = false;
			entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x + 38, p.y + 19, 31, 16, p.state));
			shoot.play();
			FirstShoot = true;
			timeShootC.restart();
		}

		// ���������� �������� ���������
		lifeBarPlayer.update(p.health);

		// ������ �� ���� ��������� �������� ������ entities
		for (it = entities.begin(); it != entities.end();)
		{
			// ��� �������� ��������� � ��������� �� ���������, ����� �� ������ (*it)->
			Entity* b = *it;

			// ������ ���������� ���� ������������ �������� �� �����
			b->update(time);
			
			// ���� ������ �����, �������� �� ������
			if (b->life == false) 
			{
				it = entities.erase(it); delete b; 
			}
			// ������� � ���������� �������
			else it++;
		}

		// ������ �� ���� ��������� �������� ������ entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// �������� ������������ �.� � ���������� ���������
			if (((*it)->name == "MovingPlatform") && ((*it)->getRect().intersects(p.getRect())))
			{
				Entity* movPlat = *it;
				// ���� �.� �� �� ����� � ����� ����
				if (((p.moveY > 0) || (p.onGround == false))&&(p.moveY>=0))
					if (p.y + p.h < movPlat->y + movPlat->h)
					{
						// ������������ �� ��������� � ��������� ��������� "�� �����" ��� �.�
						p.y = movPlat->y - p.h + 0.1; p.x += movPlat->moveX * time; p.moveY = 0;
						p.onGround = true; 
					}
			}
		


			// �������� ����������� ������ � �.�
			if ((((*it)->name == "EasyEnemy") || ((*it)->name == "RatEnemy") || ((*it)->name == "CyberEnemy") || ((*it)->name == "DroneEnemy1") || ((*it)->name == "HelloweenEnemy1") || ((*it)->name == "HelloweenEnemy2")) && ((*it)->getRect().intersects(p.getRect())))
			{
				// ���� �.� ��������� �������, �� ���� �������
				if ((p.moveY > 0) && (p.onGround == false)) {
					(*it)->moveX = 0; p.moveY = -0.4; (*it)->health = 0;
				}
				// ���� �.� � ���� ����������� �����, �� �������� ������������� � ������ ��������
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
			// �������� ����������� ������ � ���������
			if ((((*it)->name == "Hammer")) && ((*it)->getRect().intersects(p.getRect())))
			{
				p.health = 0;
			}
			// �������� ����������� ������� � ���������
			if ((((*it)->name == "Coin")) && ((*it)->getRect().intersects(p.getRect())))
			{
				(*it)->life = false;
				p.playerScore++;
			}
			// �������� ����������� �������� � ���������
			if ((((*it)->name == "Card")) && ((*it)->getRect().intersects(p.getRect())))
			{
				(*it)->life = false;
				p.playerScore += 5;
			}
			

			// ��������� ���� ������� �� ���� ��������� ������ entities
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				// ���� ����� ����� ������� �����������
				if ((*it)->getRect() != (*it2)->getRect())
					// ���� ��� ���� � ����� ����
					if (((*it)->getRect().intersects((*it2)->getRect())) && (((*it)->name == "EasyEnemy") || ((*it)->name == "CyberEnemy") || ((*it)->name == "DroneEnemy1") || ((*it)->name == "HelloweenEnemy1") || ((*it)->name == "HelloweenEnemy2")) && ((*it2)->name == "Bullet"))
					{
						// ��������� �������� ����� � ������ ����
						(*it)->health -= 50; 
						(*it2)->life = false;
						// ����������. ��� ����� ���� ����� �������� ����� ����
					}
			}
		}

		// ���� �������� ������� �� ���������� ������
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

		// ���������� �.� � ������
		updateExit(time, CurrentFrameExit, numberLevel, exitSprite);
		p.update(time);

		// ��������� ������
		window.setView(view);

		// ������� ���� � ��� �����������
		if(numberLevel == 1)
			window.clear(Color(204, 226, 225));
		if (numberLevel == 2)
			window.clear(Color(179, 175, 189));
		if (numberLevel == 3 || numberLevel == 4)
			window.clear(Color(124, 110, 122));
		
		// ��������� ������
		lvl.Draw(window); 

		// ��������� ����������� �������� ������
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite); //������ entities ������� (������ ��� ������ �����)
		}
		// ��������� ������ � �.�
		window.draw(exitSprite);
		window.draw(p.sprite);
		

		// ���������� ������ �����
		txt1.setString("Found money: " + to_string(p.playerScore));
		txt1.setPosition(view.getCenter().x - 590, view.getCenter().y - 350);
		window.draw(txt1);

		// ���������� ������ ��������
		txt2.setString("Health: " + to_string(p.health));
		txt2.setPosition(view.getCenter().x - 590, view.getCenter().y - 325);
		window.draw(txt2);

		// ���������� ������ ��-�� �������
		txt3.setString("Time: " + to_string(timePlayerAlive));
		txt3.setPosition(view.getCenter().x - 590, view.getCenter().y - 300);
		window.draw(txt3);

		// ���������� ������ ������ � ������� ��� ����
		if (!showMissionText)
		{
			// ������������ ������� ������ � ������� ���� ������
			txt4.setPosition(view.getCenter().x + 355, view.getCenter().y - 360);
			missionSprite.setPosition(view.getCenter().x + 340, view.getCenter().y - 360);
			// �����������
			window.draw(missionSprite);
			window.draw(txt4);
		}


		// ����������� ��������
		lifeBarPlayer.draw(window);
		window.display();

	}
}

// ��������� ����������� ����, ���� ��� ����������
void gameRunning(RenderWindow &window,int & numberLevel) {
	int run = startGame(window, numberLevel);
	// gameOption == 1 - ������� �������� ������
	// gameOption == 2 - ����� �� ����
	// gameOption == 3 - ������ ���������� ������
	// gameOption == 4 - ������ ������ about program
	// gameOption == 5 - ������� ���� ����
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
	// ������� �������� ������� ������
	int numberLevel = 1;
	gameRunning(window,numberLevel);
	return 0;
}