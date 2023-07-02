#include "DisplaysObjects.h"

void DisplaysObjects::move(std::vector<Shape*> shapes)
{
	for (int i = 0; i < shapes.size(); ++i)
	{
		(*shapes[i]).move();
		if (shapes[i]->isDynamic())
		{
			if (dynamic_cast<Ball*>(shapes[i]) != NULL)
			{
				for (int j = 0; j < i; ++j)
				{
					if (shapes[i]->intersects(*shapes[j]))
					{
						//ACTIONS IN CASE OF BALL COLLISION
					}
				}

				for (int k = i + 1; k < shapes.size(); ++k)
				{
					if (shapes[i]->intersects(*shapes[k]))
					{
						//ACTIONS IN CASE OF BALL COLLISION
					}
				}
			}

			if (dynamic_cast<Stand*>(shapes[i]) != NULL)
			{
				//ACTIONS IN CASE OF STAND COLLISION
			}
		}
	}
}

void DisplaysObjects::draw(std::vector<Shape*> shapes, sf::RenderWindow& window)
{
	for (const Shape* shape : shapes)
		(*shape).draw(window);
}