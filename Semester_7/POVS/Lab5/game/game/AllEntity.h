#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include <vector>
class Entity {
public:
	vector<Object> obj;
	float moveX, moveY, x, y, moveSpeed, moveTimer;
	int w, h, health;
	bool life, isMove, kickL,kickR,kickUp, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};