#pragma once
#include <SFML\Graphics.hpp>
#include "MenuItem.h"

class Menu
{
private:
	std::vector<MenuItem> m_menuItems;
	bool m_isShowMenu;
public:
	Menu(const std::vector<MenuItem>& menuItems, bool isShowMenu = true);
	void drawMenu(sf::RenderWindow& window, bool initial, std::vector<DisplaysObject*> objects = {});
	void drawSettings(sf::RenderWindow& window);
	void drawGameOver(sf::RenderWindow& window, std::vector<DisplaysObject*> objects = {});
	void drawMessageBox(sf::RenderWindow& window, std::vector<DisplaysObject*> objects);
	void initialize() const;
	void setEnable();
};

