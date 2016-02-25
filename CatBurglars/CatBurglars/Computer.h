#ifndef INCLUDED_COMPUTER
#define INCLUDED_COMPUTER

#include "Usable.h"
#include "gridvector.h"

class Computer : public Usable{
public:


	Computer(int channel, sf::Texture *texture, gridvector coords, bool toggle, float holdlength, SoundHandler *soundhandler, string face);
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	virtual bool getInteraction(GameObject *g);
	virtual int getChannelID();
	virtual bool isSolid();

	virtual bool isInteracting();
	virtual Layer getLayer();
private:
	string mFace;
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	int mChannelID;

	bool mToggle;
	float mHoldlength;

	SoundHandler *mSoundHandler;
	sf::Sound mInteractedSound;
};



#endif