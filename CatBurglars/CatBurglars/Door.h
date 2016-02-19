#pragma once
#include "Recievers.h"
#include "Channels.h"
class Door : public Recievers{
public:
	Door(int channel, gridvector coords, sf::Texture *texture);
	virtual void connectToChannel(int channelID);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();
	virtual bool isSolid();
	virtual bool isInteracting();
	virtual Layer getLayer();
private:
	int mChannel;
	bool mSolid;
	sf::Vector2i mPosition;
	gridvector mCoords;
	sf::Sprite mSprite;
};
//m�ste ha tv� sprites, b�da inneh�ller cameran, den andra inneh�ller en genomskinlig zon som �r d�ri man blir hittad, den andra inneh�ller bara cameran och �r fortfarande "p�"