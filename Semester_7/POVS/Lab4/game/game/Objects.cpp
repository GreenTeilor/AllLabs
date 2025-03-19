#include "Objects.h"
void Objects::getObjetsFromMap(Level lvl) 
{
	e = lvl.GetObjects("EasyEnemy");
	//for (int i = 0; i < e.size(); i++)
		// ƒобавление в список врагов из вектора
		//entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 64, 64, 3000));
}