#include "MenuButton.h"
#include <iostream>

MenuButton::MenuButton() :
	Options(),
	isSelected(false),
	isPushed(false){
}

bool MenuButton::isButtonPushed() {
	return isPushed;
}

void MenuButton::pushButton() {
	isPushed = true;
}
void MenuButton::releaseButton() {
	isPushed = false;
}

void MenuButton::setTexture(sf::Texture *text) {
	buttonTexture = *text;
	mSize = (sf::Vector2f)buttonTexture.getSize();
}
void MenuButton::setTextureSelected(sf::Texture *text) {
	buttonSelectedTexture = *text;
	mSize = (sf::Vector2f)buttonSelectedTexture.getSize();
}
void MenuButton::setPosition(sf::Vector2f pos){
	mPosition = pos;
}
sf::Vector2f MenuButton::getPosition() {
	return mPosition;
}
void MenuButton::render(sf::RenderWindow *window) {
	if (isSelected) {
		mSprite.setTexture(buttonSelectedTexture);
	}
	else {
		mSprite.setTexture(buttonTexture);
	}
	mSprite.setPosition(mPosition);
	window->draw(mSprite);
}
sf::Vector2f MenuButton::getSize() {
	return mSize;
}