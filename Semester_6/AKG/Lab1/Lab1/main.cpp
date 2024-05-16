#include <string>
#include "ObjParser.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>
#include "Brezenhem.h"
#include "Coordinates.h"
#include "ProcessCoordinates.h"
#include <thread>
#include "ThreadPool.h"
#include <winuser.h>

#define TIMER

#ifdef TIMER
#include <chrono>
#endif

using namespace sf;

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define THREADS_AMOUNT 6

double parseTime = 0.0;

//CLEAR VECTOR PASSED AS A PARAMETER TO FREE MEMORY SPACE
template <typename T>
std::vector<std::vector<T>> createFragments(std::vector<T>& vector, const int fragmentsCount)
{
	std::vector<std::vector<T>> fragments{};
	fragments.resize(fragmentsCount);
	int fragmentSize = vector.size() / fragmentsCount;
	int lastFragmentSize = vector.size() - fragmentSize * (fragmentsCount - 1);
	for (int i = 0; i < fragmentsCount - 1; ++i)
	{
		for (int j = i * fragmentSize; j < (i + 1) * fragmentSize; ++j)
		{
			fragments[i].push_back(vector[j]);
		}
	}
	for (int i = vector.size() - lastFragmentSize; i < vector.size(); ++i)
	{
		fragments[fragments.size() - 1].push_back(vector[i]);
	}
	return fragments;
}

void processCoordinates(const std::vector<std::vector<Face>>& faces, const glm::mat4& mvp, std::vector<Coordinates>& viewPortCoordinates, int threadsAmount)
{
	//HANDLE* threads = (HANDLE*)malloc(sizeof(HANDLE) * threadsAmount);
	std::vector<std::thread> threads{};
	for (int i = 0; i < threadsAmount; ++i)
	{
		ProcessCoordinates::Params params{ faces[i], mvp, viewPortCoordinates};
		threads.push_back(std::thread(&ProcessCoordinates::process, &params)/*CreateThread(NULL, 0, &ProcessCoordinates::process, (LPVOID)&params, NULL, NULL)*/);
	}
	for (auto& t : threads) {
		t.join();
	}
}

std::vector<std::thread> threads{ std::thread::hardware_concurrency() };


struct TestTask : public MT::Task {
	glm::ivec2 firstPoint;
	glm::ivec2 secondPoint;
	sf::Image& image;
	glm::mat4& mvp;
	std::vector<Face>& fragment;

	TestTask(const std::string& id, const glm::ivec2& firstPoint, const glm::ivec2& secondPoint, 
		sf::Image& image, glm::mat4& mvp, std::vector<Face>& fragment) : Task(id), image{ image }, firstPoint{ firstPoint }, fragment{ fragment },
		secondPoint{ secondPoint }, mvp{ mvp } {
	};

	void one_thread_method() override {
		for (size_t j = 0; j < fragment.size(); j++) {
			std::vector<std::vector<float>>& currentFace = fragment.at(j).getV();
			for (size_t k = 0; k < currentFace.size(); k++) {

				size_t vertNum = currentFace.size();
				size_t currInd = k;
				size_t nextInd = (k + 1) % vertNum;
				std::vector<float>& currentvertex = currentFace.at(currInd);
				std::vector<float>& nextvertex = currentFace.at(nextInd);
				glm::vec4 currVertVector = mvp * glm::vec4{ currentvertex.at(0), currentvertex.at(1), currentvertex.at(2), 1.0f };
				glm::vec4 nextVertVector = mvp * glm::vec4{ nextvertex.at(0), nextvertex.at(1), nextvertex.at(2), 1.0f };
				currVertVector /= currVertVector.w;
				nextVertVector /= nextVertVector.w;

				Brezenhem::processPoints(currVertVector, nextVertVector, image);
			}
		}
	}
};


int main()
{
	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "3D!", sf::Style::Close | sf::Style::Titlebar);
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);
	//HWND hwnd = window.getSystemHandle();
	Brezenhem::init();
	threads.resize(THREADS_AMOUNT);
	CRITICAL_SECTION mutex;
	InitializeCriticalSection(&mutex);
	//ProcessCoordinates::init();
#ifdef TIMER 
	auto beg = std::chrono::high_resolution_clock::now();
#endif
	std::string path{ "Cat.obj" };
	ObjParser parser{ path };

	std::vector<Face> faces = parser.parse();
	std::vector<std::vector<Face>> facesFragments = createFragments(faces, THREADS_AMOUNT);
	/*===========MATRICES HERE!!!========*/

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 proj = glm::perspective(glm::radians(90.f), static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.1f, 100.0f);

	glm::vec3 cameraPos = glm::vec3(-40.0f, 1.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);

	glm::mat4 viewport = glm::mat4(
		SCREEN_WIDTH / 2, 0, 0, 0,
		0, -SCREEN_HEIGHT / 2, 0, 0,
		0, 0, 1, 0,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1
	);

	float lastX = SCREEN_WIDTH / 2;
	float lastY = SCREEN_HEIGHT / 2;
	bool firstMouse = true;
	float yaw = 0.f;
	float pitch = 0.f;

	glm::mat4 mvp = viewport * proj * view * model;

#ifdef TIMER
	std::cout << "Parse time: " << parseTime << std::endl;
	std::chrono::duration<double> time;
#endif
	sf::Texture texture{};
	texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

	std::chrono::time_point currentFrame = std::chrono::system_clock::now();
	std::chrono::time_point lastFrame = std::chrono::system_clock::now();
	//RECT clipRect{};
	//GetWindowRect(hwnd, &clipRect);
	//ClipCursor(&clipRect);
	//SetCursorPos(clipRect.right / 2, clipRect.bottom);
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//auto currentFrame = std::chrono::system_clock::now();
		//auto deltaTime = currentFrame - lastFrame;
		//auto lastFrame = currentFrame;
		//const float cameraSpeed = 0.0000001f * deltaTime.count();
		const float cameraSpeed = 0.2f;

		sf::Image image;
		image.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W)
				{
					cameraPos += cameraSpeed * cameraDirection;
				}
				else if (event.key.code == Keyboard::S)
				{
					cameraPos -= cameraSpeed * cameraDirection;
				}
				else if (event.key.code == Keyboard::A)
				{
					cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
				}
				else if (event.key.code == Keyboard::D)
				{
					cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
				}
				else if (event.key.code == Keyboard::C)
				{
					glm::vec3 saved = cameraRight;
					cameraRight = cameraUp;
					cameraUp = -saved;
				}
			}
			else if (event.type == Event::MouseMoved)
			{
				static glm::vec2 lastMousePos;
				glm::vec2 mousePos(event.mouseMove.x, event.mouseMove.y);
				if (firstMouse) // изначально установлено значение true
				{
					lastMousePos.x = mousePos.x;
					lastMousePos.y = mousePos.y;
					firstMouse = false;
				}

				float xoffset = mousePos.x - lastMousePos.x;
				float yoffset = lastMousePos.y - mousePos.y;
				const float sensivity = 0.05f;

				float sensitivity = 0.05;
				xoffset *= sensitivity;
				yoffset *= sensitivity;

				yaw += xoffset;
				pitch += yoffset;

				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;

				glm::vec3 direction;
				direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
				direction.y = sin(glm::radians(pitch));
				direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
				cameraDirection = glm::normalize(direction);

				auto windowSize = window.getSize();
				uint32_t maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 3;
				glm::vec2 windowCenter(windowSize.x / 2, windowSize.y / 2);

				if (glm::length(mousePos - windowCenter) > maxMousePosRadius) {
					sf::Mouse::setPosition(sf::Vector2i((int)windowCenter.x, (int)windowCenter.y), window);
					lastMousePos = windowCenter;
				}
				else {
					lastMousePos = mousePos;
				}	
			}
		}
		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
		mvp = viewport * proj * view * model;

#ifdef TIMER
		auto calcBeg = std::chrono::high_resolution_clock::now();
#endif
		for (int i = 0; i < threads.size(); ++i)
		{
			auto& fragment = facesFragments[i];
			threads[i] = std::thread([&, i]()
				{
					for (size_t j = 0; j < fragment.size(); j++) {
						std::vector<std::vector<float>>& currentFace = fragment.at(j).getV();
						for (size_t k = 0; k < currentFace.size(); k++) {

							size_t vertNum = currentFace.size();
							size_t currInd = k;
							size_t nextInd = (k + 1) % vertNum;
							std::vector<float>& currentvertex = currentFace.at(currInd);
							std::vector<float>& nextvertex = currentFace.at(nextInd);
							glm::vec4 currVertVector = mvp * glm::vec4{ currentvertex.at(0), currentvertex.at(1), currentvertex.at(2), 1.0f };
							glm::vec4 nextVertVector = mvp * glm::vec4{ nextvertex.at(0), nextvertex.at(1), nextvertex.at(2), 1.0f };
							currVertVector /= currVertVector.w;
							nextVertVector /= nextVertVector.w;

							Brezenhem::processPoints(currVertVector, nextVertVector, image);
						}
					}
				}
			);

		}

		for (auto& thread : threads)
			thread.join();

#ifdef TIMER
		std::chrono::duration<double> calcTime = std::chrono::high_resolution_clock::now() - calcBeg;
		std::cout << "Time for coordinates calcutions: " << calcTime.count() << std::endl;
#endif

#ifdef TIMER
		auto paintBeg = std::chrono::high_resolution_clock::now();
#endif
		window.clear(sf::Color::Black);
		texture.update(image);
		window.draw(sf::Sprite{texture});
		// Отрисовка окна	
		window.display();

#ifdef TIMER
		std::chrono::duration<double> paintTime = std::chrono::high_resolution_clock::now() - paintBeg;
		std::cout << "Time for frame paint: " << paintTime.count() << std::endl;
#endif

#ifdef TIMER
		time = std::chrono::high_resolution_clock::now() - beg;
		std::cout << "Time passed since start of the program: " << time.count() << std::endl;
#endif
	}


	return 0;

}