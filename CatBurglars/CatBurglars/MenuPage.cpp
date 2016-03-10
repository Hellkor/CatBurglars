#include "MenuPage.h"
#include <iostream>
#include <SFML\Window\Keyboard.hpp>
using namespace std;
MenuPage::MenuPage(sf::Vector2f pos, string name) :
	Options(),
	mIndex(0),
	mCoolDown(sf::milliseconds(200)),
	mKeyUp(sf::Keyboard::Up),
	mkeyDown(sf::Keyboard::Down),
	mName(name){
	Options.buttonListPosition = pos; 
	buttonAddPos = pos;
	MenuIndex = mIndex;

	mDelayClock.restart();
}


string MenuPage::getName() {
	return mName;
}
void MenuPage::addMenuButton(MenuButton *button) {

	button->setPosition(buttonAddPos);
	Buttons.push_back(button);

	buttonAddPos.y += button->getSize().y + Options.spaceBetweenButtons.y;

	Buttons[0]->isSelected = true;
}
void MenuPage::selectMenuButton(int i) {
	Buttons[mIndex]->isSelected = false;
	Buttons[i]->isSelected = true;
	mIndex = i;
}
void MenuPage::activateButton() {
	Buttons[mIndex]->pushButton(); 
}
void MenuPage::render(sf::RenderWindow *window) {
	for each (MenuButton *b in Buttons) {
		b->render(window);
	}
}
void MenuPage::setNavigation(sf::Keyboard::Key moveUp, sf::Keyboard::Key moveDown) {
	mKeyUp = moveUp;
	mkeyDown = moveDown;
}
void MenuPage::setCooldown(sf::Time time) {
	mCoolDown = time;
}
void MenuPage::releaseButton() {
	Buttons[mIndex]->releaseButton();
}
void MenuPage::resetPage() {
	mDelayClock.restart();
	releaseButton();
}
void MenuPage::UpdatedMenuNavigation() {
	
	releaseButton();

	if (mDelayClock.getElapsedTime().asMilliseconds() >= mCoolDown.asMilliseconds()) {
		
		if (sf::Keyboard::isKeyPressed(mKeyUp)) {
			mDelayClock.restart();
			if (MenuIndex > 0) {
				MenuIndex--;
				selectMenuButton(MenuIndex);
			}
		}
		else if (sf::Keyboard::isKeyPressed(mkeyDown)) {
			mDelayClock.restart();
			if (MenuIndex < Buttons.size() -1) {
				MenuIndex++;
				selectMenuButton(MenuIndex);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			activateButton();
			mDelayClock.restart();
		}

	}
}

// : )