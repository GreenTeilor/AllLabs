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
	// ������ ��� ��������(�����, ����, ���������, ������)
	static list<Entity*>  entities;
	// ��������� ������� �� ���� ��������� ������
	list<Entity*>::iterator it;
	list<Entity*>::iterator it2;
};
