#pragma once
#include <vector>
#include "level.h"
#include <list>
#include "AllEntity.h"
using namespace std;
class Objects
{
public:
	static vector<Object> e;
	static void getObjetsFromMap(Level lvl);
	// Список для объектов(враги, пули, платформы, монеты)
	static list<Entity*>  entities;
	// Итераторы прохода по всем элементам списка
	list<Entity*>::iterator it;
	list<Entity*>::iterator it2;
};
