#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "level.h"
using namespace sf;
using namespace std;
class Entity {
public:
	vector<Object> obj;
	float moveX, moveY, x, y, moveSpeed, moveTimer;
	int w, h, health;
	bool life, isMove, kickL, kickR, kickUp, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};