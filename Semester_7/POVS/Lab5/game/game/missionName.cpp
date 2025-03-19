#include "missionName.h"

using namespace std;

// Фу-я возвращает текст миссия в зависимости от переданного номера
string getTextByMissionNum(int currMissionNum)
{
	// Инициализация текста миссии
	string missionText = "";
	// Параметр - номер миссии
	switch (currMissionNum)
	{
	case 1: missionText = "\nTraining\n find fountain"; break;
	case 2: missionText = "\nHardcore\n find screen"; break;
	case 3: missionText = "\nHelloween\n find pumpkin?!"; break;
	case 4: missionText = "\n Thx for\n playing! :)"; break;
	default:
		break;
	}
	return missionText;
}