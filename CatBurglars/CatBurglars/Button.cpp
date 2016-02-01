#include "Button.h"
#include "Channels.h"

int INTERACTION_RADIUS = 20;


Button::Button(int channel, sf::Texture *texture,sf::Vector2i vec) :
	Usable(),
	mChannelID(channel),
	mPosition(vec){
	mSprite.setPosition(sf::Vector2f(mPosition));
	mSprite.setTexture(*texture);
	
}


int Button::getChannelID(){
	return mChannelID;
}

int length(sf::Vector2i v1, sf::Vector2i v2){
	int length;
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;

	length = sqrt((dy * dy) + (dx * dx));
	return length;
}

bool Button::getInteraction(Cat *cat){
	
	
	
		if (length(mPosition, cat->GetPosition()) < INTERACTION_RADIUS){
			//if (cat->interacting()){
					// activate channel
					Channels::setActive(mChannelID, false, 1);
					// play sound
					return true;
			//}
		}
		
}


sf::Vector2i Button::GetPosition(){
	return mPosition;
}

void Button::Render(sf::RenderWindow *window){

	window->draw(mSprite);
}
void Button::Update(){

}

