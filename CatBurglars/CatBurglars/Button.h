#ifndef INCLUDED_BUTTON
#define INCLUDED_BUTTON

#include "Usable.h"
#include "gridvector.h"

class Button : public Usable{
public:

	Button(int ID, sf::Texture *texture, gridvector coords,bool toggle,float holdlength);
	virtual ~Button();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	virtual bool getInteraction(GameObject *g);
	virtual int getChannelID();
	virtual bool isSolid();

	virtual bool isInteracting();
	virtual Layer getLayer();

	bool Activate(sf::Time active_time);
	bool playSound();
private:

	void activateChannel();

	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	int mChannelID;

	bool mToggle;
	float mHoldlength;


	sf::Clock mButtonPressClock;
	sf::Time mButtonPressTime;


	sf::Time mChannelHold;
	sf::Clock ChannelClock;
	bool channelActive;

	sf::Font mFont;
	sf::Text timerText;


};



#endif