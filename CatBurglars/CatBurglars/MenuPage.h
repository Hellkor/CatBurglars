#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>
#include "MenuButton.h"
struct Options {
	sf::Vector2f buttonListPosition;
	sf::Vector2f spaceBetweenButtons; // x = x spacing , y = y spacing

	enum ORIENTATION { HORIZONTAL, VERTICAL };
	ORIENTATION Orientation = VERTICAL;
};
class MenuPage {
	
public:
	MenuPage(sf::Vector2f pos,std::string name);
	Options Options;
	void addMenuButton(MenuButton *button);
	void render(sf::RenderWindow *window);

	void selectMenuButton(int i);

	void activateButton();

	void UpdatedMenuNavigation();
	void setNavigation(sf::Keyboard::Key moveUp, sf::Keyboard::Key moveDown);
	void setCooldown(sf::Time cooldown);

	void resetPage();

	
	
	std::string getName();
private:
	void releaseButton();
	std::string mName;
	sf::Vector2f buttonAddPos;
	MenuButton *mSelectedButton;
	std::vector<MenuButton*> Buttons;

	sf::Keyboard::Key mKeyUp;
	sf::Keyboard::Key mkeyDown;
	
	sf::Clock mDelayClock;
	sf::Time mCoolDown;

	int mIndex;
	int MenuIndex;
};