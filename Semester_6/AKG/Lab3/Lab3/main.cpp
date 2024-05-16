#include <string>
#include "ObjParser.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Graphics.hpp>
#include "Algorithms.h"
#include <thread>
#include <winuser.h>

//#define TIMER

#ifdef TIMER
#include <chrono>
#endif

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define THREADS_AMOUNT 6

#define OBJECT_COLOR sf::Color{247, 194, 2}

#define AMBIENT_LIGHT_STRENGTH 0.1f / 255.0f
#define LIGHT_COLOR sf::Color::White
#define OBJECT_COLOR_COMPONENTS glm::vec3{ OBJECT_COLOR.r, OBJECT_COLOR.g, OBJECT_COLOR.b }
#define LIGHT_COLOR_COMPONENTS glm::vec3{ LIGHT_COLOR.r, LIGHT_COLOR.g, LIGHT_COLOR.b }

#define DIFFUSE_LIGHT_STRENGTH 0.0029f
#define DIFFUSE_LIGHT_COLOR sf::Color::White
#define DIFFUSE_LIGHT_COLOR_COMPONENTS glm::vec3{ DIFFUSE_LIGHT_COLOR.r, DIFFUSE_LIGHT_COLOR.g, DIFFUSE_LIGHT_COLOR.b }

#define SPECULAR_STRENGTH 0.25f

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

std::vector<std::thread> threads{ std::thread::hardware_concurrency() };
double parseTime = 0.0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "3D!", sf::Style::Close | sf::Style::Titlebar);
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);
	Algorithms::init();
	threads.resize(THREADS_AMOUNT);
	CRITICAL_SECTION mutex;
	InitializeCriticalSection(&mutex);

#ifdef TIMER 
	auto beg = std::chrono::high_resolution_clock::now();
#endif

	std::string path{ "Cat.obj" };
	ObjParser parser{ "../Assets/" + path};

	std::vector<Face> faces = parser.parse();
	std::vector<std::vector<Face>> facesFragments = createFragments(faces, THREADS_AMOUNT);

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

	std::vector<float> zBuffer(SCREEN_WIDTH * SCREEN_HEIGHT, INT_MAX);

	while (window.isOpen())
	{
		const float cameraSpeed = 0.2f;
		sf::Image image;
		image.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		std::fill(zBuffer.begin(), zBuffer.end(), INT_MAX);

		sf::Event event;
		while (window.pollEvent(event))
		{ 
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					cameraPos += cameraSpeed * cameraDirection;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					cameraPos -= cameraSpeed * cameraDirection;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
				}
				else if (event.key.code == sf::Keyboard::C)
				{
					glm::vec3 saved = cameraRight;
					cameraRight = cameraUp;
					cameraUp = -saved;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				static glm::vec2 lastMousePos;
				glm::vec2 mousePos(event.mouseMove.x, event.mouseMove.y);
				if (firstMouse) // Initially true
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
					for (size_t j = 0; j < fragment.size(); j++) 
					{
						std::vector<std::vector<float>>& faceVertices = fragment.at(j).getV();
						std::vector<std::vector<float>>& faceNormals = fragment.at(j).getVN();

						std::vector<float>& vert0 = faceVertices.at(0);
						std::vector<float>& vert1 = faceVertices.at(1);
						std::vector<float>& vert2 = faceVertices.at(2);

						glm::vec3 worldVert0{ vert0.at(0), vert0.at(1), vert0.at(2) };
						glm::vec3 worldVert1{ vert1.at(0), vert1.at(1), vert1.at(2) };
						glm::vec3 worldVert2{ vert2.at(0), vert2.at(1), vert2.at(2) };

						std::vector<float>& normal0 = faceNormals.at(0);
						std::vector<float>& normal1 = faceNormals.at(1);
						std::vector<float>& normal2 = faceNormals.at(2);

						glm::vec4 calcVert0{ mvp * glm::vec4{ vert0.at(0), vert0.at(1), vert0.at(2), 1.0f } };
						glm::vec4 calcVert1{ mvp * glm::vec4{ vert1.at(0), vert1.at(1), vert1.at(2), 1.0f } };
						glm::vec4 calcVert2{ mvp * glm::vec4{ vert2.at(0), vert2.at(1), vert2.at(2), 1.0f } };

						glm::vec3 normalVec0{ normal0.at(0), normal0.at(1), normal0.at(2) };
						glm::vec3 normalVec1{ normal1.at(0), normal1.at(1), normal1.at(2) };
						glm::vec3 normalVec2{ normal2.at(0), normal2.at(1), normal2.at(2) };

						calcVert0 /= calcVert0.w;
						calcVert1 /= calcVert1.w;
						calcVert2 /= calcVert2.w;

						glm::vec3 edge1{ vert1.at(0) - vert0.at(0), vert1.at(1) - vert0.at(1), vert1.at(2) - vert0.at(2) };
						glm::vec3 edge2{ vert2.at(0) - vert0.at(0), vert2.at(1) - vert0.at(1), vert2.at(2) - vert0.at(2) };
						glm::vec3 normal{ glm::cross(edge1, edge2) };

						glm::vec3 reversePolygonCameraDirection{ cameraPos.x - vert0[0], cameraPos.y - vert0[1], cameraPos.z - vert0[2]};
						float scalar = glm::dot(normal, reversePolygonCameraDirection);
						
						if (scalar > 0)
						{
							std::vector<glm::vec4> vertices{ calcVert0, calcVert1, calcVert2 };
							std::vector<glm::vec3> normalVectors{ normalVec0, normalVec1, normalVec2 };
							std::vector<glm::vec3> worldVertices{ worldVert0, worldVert1, worldVert2 };
							glm::vec3 colorComponents{ AMBIENT_LIGHT_STRENGTH * LIGHT_COLOR_COMPONENTS };
							sf::Color color{ (sf::Uint8)colorComponents[0], (sf::Uint8)colorComponents[1], (sf::Uint8)colorComponents[2] };
							Algorithms::rasterTriangle(vertices, worldVertices, normalVectors, cameraPos, image, colorComponents,
								zBuffer, (calcVert0.z + calcVert1.z + calcVert2.z) * 0.33333, DIFFUSE_LIGHT_STRENGTH, DIFFUSE_LIGHT_COLOR_COMPONENTS, OBJECT_COLOR_COMPONENTS, SPECULAR_STRENGTH, mvp);
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