#include "ProcessCoordinates.h"
#include "Brezenhem.h"

CRITICAL_SECTION ProcessCoordinates::mutex{};

void ProcessCoordinates::init()
{
	InitializeCriticalSection(&mutex);
}

DWORD WINAPI ProcessCoordinates::process(LPVOID vParams)
{
	/*
	Params* params = (Params*)vParams;
	for (size_t i = 0; i < params->faces.size(); i++) {
		std::vector<std::vector<float>> currentFace = params->faces.at(i).getV();
		for (size_t j = 0; j < currentFace.size(); j++) {

			size_t vertNum = currentFace.size();
			size_t currInd = j;
			size_t nextInd = (j + 1) % vertNum;
			std::vector<float> currentvertex = currentFace.at(currInd);
			std::vector<float> nextvertex = currentFace.at(nextInd);
			glm::vec4 currVertVector = params->mvp * glm::vec4{ currentvertex.at(0), currentvertex.at(1), currentvertex.at(2), 1.0f };
			glm::vec4 nextVertVector = params->mvp * glm::vec4{ nextvertex.at(0), nextvertex.at(1), nextvertex.at(2), 1.0f };
			currVertVector /= currVertVector.w;
			nextVertVector /= nextVertVector.w;

			EnterCriticalSection(&mutex);
			Brezenhem::processPoints(currVertVector, nextVertVector, params->viewPortCoordinates, true);
			LeaveCriticalSection(&mutex);
		}
	}
	*/
	return 0;
}