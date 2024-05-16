#pragma once
#include <windows.h>
#include <vector>
#include "Face.h"
#include <glm/glm.hpp>
#include "Coordinates.h"

class ProcessCoordinates
{
private:
	static CRITICAL_SECTION mutex;

public:
	struct Params
	{
		const std::vector<Face>& faces;
		const glm::mat4& mvp;
		std::vector<Coordinates>& viewPortCoordinates;
	};
	static void init();
	static DWORD WINAPI process(LPVOID vParams);
};

