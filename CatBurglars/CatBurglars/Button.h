#ifndef INCLUDED_BUTTON
#define INCLUDED_BUTTON

#include "Usable.h"
#include "gridvector.h"

class Button : public Usable{
public:

	Button(int ID, sf::Texture *texture, gridvector coords);
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();

	virtual bool getInteraction(Cat *c);
	virtual int getChannelID();
	virtual bool isSolid();

private:
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	int mChannelID;


};



#endif