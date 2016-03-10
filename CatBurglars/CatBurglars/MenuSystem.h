#pragma once
#include "MenuPage.h"
#include <SFML\Graphics.hpp>
#include <string>
class MenuSystem {

public:
	MenuSystem();
	void addPage(MenuPage *page);
	void render(sf::RenderWindow *window);
	void setPage(std::string name);

	void UpdateNavigation();
private:
	std::vector<MenuPage*> Pages;
	MenuPage *mActivePage;
};