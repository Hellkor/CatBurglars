#include "Computer.h"
#include "Channels.h"
#include "Cat.h"
#include <string>
#include <sstream>
#include <iomanip>
int COMPUTER_INTERACTION_RADIUS = 20;


Computer::Computer(int channel, sf::Texture *texture, gridvector coords, bool toggle, float holdlength, SoundHandler *soundhandler,string face) :
Usable(),
mChannelID(channel),
mCoords(coords),
mToggle(toggle),
mHoldlength(holdlength),
mSoundHandler(soundhandler),
mFace(face)
{

	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	timerText.setFont(mFont);
	timerText.setCharacterSize(24);

	mInteractedSound.setBuffer(*mSoundHandler->getSound(3));
	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;
	if (mFace == "S") {
		spriteposx = 0;
		spriteposy = 0;
		//mSprite.setTextureRect(sf::IntRect(0 * 64, 0 * 64, 64, 128));
		timerText.setPosition(sf::Vector2f(mPosition.x + 32, mPosition.y - 64));
	}
	if (mFace == "E") {
		spriteposx = 1;
		spriteposy = 0;
		//mSprite.setTextureRect(sf::IntRect(1 * 64, 0 * 64, 64, 128));
		timerText.setPosition(sf::Vector2f(mPosition.x - 32, mPosition.y - 32));
	}
	if (mFace == "W") {
		spriteposx = 2;
		spriteposy = 0;
		//mSprite.setTextureRect(sf::IntRect(2 * 64, 0 * 64, 64, 128));
		timerText.setPosition(sf::Vector2f(mPosition.x + 32, mPosition.y - 32));
	}
	mChannelHold = sf::seconds(holdlength);
	
	mSprite.setPosition(sf::Vector2f(mPosition.x,mPosition.y - 64));
	mSprite.setTexture(*texture);
	

}
Computer::~Computer()
{
}
bool Computer::isSolid(){
	return false;
}
int Computer::getChannelID(){
	return mChannelID;
}

int computerLength(sf::Vector2i v1, sf::Vector2i v2){
	int length;
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;

	length = sqrt((dy * dy) + (dx * dx));
	return length;
}

bool Computer::getInteraction(GameObject *g){
	return false;
}
string Computer::getFace() {
	return mFace;
}
bool Computer::Activate(sf::Time active_time) {
	if (!gettingHacked) {
		activateDelay = active_time;
		activateClock.restart();
		gettingHacked = true;
		return true;
	}
	else return false;
}
bool Computer::playSound() {
	if (mInteractedSound.getStatus() != sf::Sound::Playing) {
		mInteractedSound.play();
	}
	
	return true;
}
void Computer::activateChannel() {
	Channels::activate(mChannelID);
	//change sheet
	channelActive = true;
}
Layer Computer::getLayer() {
	return OnWallUsables;
}
sf::Vector2i Computer::GetPosition(){
	return mPosition;
}

void Computer::Render(sf::RenderWindow *window){
	if (channelActive) {
		spriteposy = 1;
	}
	else if (!channelActive) {
		spriteposy = 0;
	}
	mSprite.setTextureRect(sf::IntRect(spriteposx * 64, spriteposy * 128, 64, 128));
	if (!mToggle && channelActive) {
		double time = (int)mChannelHold.asSeconds() + 1 - activateClock.getElapsedTime().asSeconds();
		
		stringstream stream;
		stream << fixed << setprecision(0) << time;
		string s = stream.str();
		timerText.setString(s);

		window->draw(timerText);
	}
	
	window->draw(mSprite);
}
void Computer::Update(float dt){
	if (!mToggle) {
		if (gettingHacked) {
			if (activateClock.getElapsedTime().asSeconds() > activateDelay.asSeconds()) {
				gettingHacked = false;
				Channels::activate(mChannelID);
				ChannelClock.restart();
				channelActive = true;
			}
		}
		if (channelActive) {
			if (ChannelClock.getElapsedTime().asSeconds() >= mChannelHold.asSeconds()) {
				Channels::deactivate(mChannelID);
				channelActive = false;
			}
		}
	}
	else if (mToggle) {
		if (gettingHacked) {
			if (activateClock.getElapsedTime().asSeconds() > activateDelay.asSeconds()) {
				
					gettingHacked = false;
					if (channelActive) {
						Channels::deactivate(mChannelID);
						channelActive = false;
					}
					else if (!channelActive) {
						Channels::activate(mChannelID);
						channelActive = true;
					}
					
					//channelActive = !channelActive;
				
			}
			
		}
		
	}
}
bool Computer::isInteracting(){
	return false;
}
gridvector Computer::getCoords(){
	return mCoords;
}
