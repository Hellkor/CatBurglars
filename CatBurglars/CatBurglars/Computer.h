#ifndef INCLUDED_COMPUTER
#define INCLUDED_COMPUTER

#include "Usable.h"
#include "gridvector.h"

class Computer : public Usable{
public:

	Computer(int ID, sf::Texture *texture, gridvector coords, bool toggle, float holdlength);
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	virtual bool getInteraction(GameObject *g);
	virtual int getChannelID();
	virtual bool isSolid();

	virtual bool isInteracting();

private:
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	int mChannelID;

	bool mToggle;
	float mHoldlength;


};



#endif