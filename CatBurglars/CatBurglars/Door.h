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
//måste ha två sprites, båda innehåller cameran, den andra innehåller en genomskinlig zon som är däri man blir hittad, den andra innehåller bara cameran och är fortfarande "på"