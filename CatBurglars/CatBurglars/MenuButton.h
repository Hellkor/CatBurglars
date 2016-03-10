#pragma once
#include <SFML\Graphics.hpp>

enum ButtonType {Normal,Scroll};
class MenuButton {
	struct Options {
		bool enableText;
		sf::Vector2f textOffset;
		float fontSize;
		void setFont(sf::Font font);
	private:
		sf::Font mFont;
	};
public:
	MenuButton();
	Options Options;

	void pushButton();
	bool isSelected;
	void setTexture(sf::Texture *text);
	void setTextureSelected(sf::Texture *text);
	void setFont(sf::Font *font);

	void render(sf::RenderWindow *window);
	bool isButtonPushed();

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void releaseButton();
	sf::Vector2f getSize();
private:
	ButtonType mType;
	bool isPushed;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::Vector2f mSize;
	sf::Texture buttonTexture;
	sf::Texture buttonSelectedTexture;

	
};