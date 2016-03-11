#include "Button.h"
#include "Channels.h"

int INTERACTION_RADIUS = 20;


Button::Button(int channel, sf::Texture *texture, gridvector coords, bool toggle, float holdlength) :
	Usable(),
	mChannelID(channel),
	mCoords(coords),
	mToggle(toggle),
	mHoldlength(holdlength){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;
	mSprite.setPosition(sf::Vector2f(mPosition));
	mSprite.setTexture(*texture);
	
}
Button::~Button()
{
}
bool Button::isSolid(){
	return false;
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

bool Button::getInteraction(GameObject *g){

		if (length(mPosition, g->GetPosition()) < INTERACTION_RADIUS && g->isInteracting()){
					// activate channel
					Channels::setActive(mChannelID, mToggle, mHoldlength);
					// play sound
					return true;
		}
		
}
bool Button::Activate(sf::Time time) {
	//activateChannel();
	Channels::setActive(mChannelID, mToggle, mHoldlength);
	return true;
}
bool Button::playSound() {
	//play sound
	return true;
}
void Button::activateChannel() {
	Channels::setActive(mChannelID, mToggle, mHoldlength);
}
sf::Vector2i Button::GetPosition(){
	return mPosition;
}

void Button::Render(sf::RenderWindow *window){

	window->draw(mSprite);
}
void Button::Update(float dt){

}
bool Button::isInteracting(){
	return false;
}
gridvector Button::getCoords(){
	return mCoords;
}
Layer Button::getLayer() {
	return BACK;
}